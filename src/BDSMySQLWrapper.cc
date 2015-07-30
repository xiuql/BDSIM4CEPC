/* * BDSIM code.    Version 1.0
   * Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   * Last modified 24.7.2002
   * Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 


   Author of this code: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 12.10.2005
*/

#include "BDSGlobalConstants.hh" 
#include "BDSDebug.hh"

#include "BDSMySQLWrapper.hh"
#include "BDSMySQLTable.hh"

#include "globals.hh"
#include <cstdlib>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#
BDSMySQLWrapper::BDSMySQLWrapper (const G4String& SQLFileName)
  : ifs(SQLFileName.c_str()), ComponentN(0), tableN(-1)
  
{
  _startOfFile=true;
  BeginTokens();

  if(ifs) {
#ifdef BDSDEBUG
    G4cout<<"BDSMySQLWrapper contructor: Loading SQL Filename="<<SQLFileName<<G4endl;
#endif
  }
  else {
    G4cout<<"BDSMySQLWrapper constructor: Unable to load SQL file: "<<SQLFileName<<G4endl;
    exit(1);
  }
}

BDSMySQLWrapper::~BDSMySQLWrapper()
{
}

std::vector<BDSMySQLTable*> BDSMySQLWrapper::ConstructTable ()
{
  ComponentN=0;
  tableN=-1;
  while(NextToken()){
    ParseComponent();
  }
  return table;
}

void BDSMySQLWrapper::TokenizeLine(){
  // empty old tokens
  _tokens.clear();

  // Separate with comma and space, separate and keep with ; ( ) and \n
  // Done in 2 steps, once for dropped delimiters and then for the kept delimiters
  // Delimiters are spaces (no tabs!) and/or commas
  std::regex drop_delimiters("[ ,]+");

  std::string &s = _currentLine;
  // Specifying -1 as the fourth argument makes the function skip over any patterns matching the regex_obj, causing the iterator to iterate through the tokens—which consist of text between each occurrence of the pattern.
  std::sregex_token_iterator tok_iter(s.begin(), s.end(), drop_delimiters, -1);
  
  // default constructor = end-of-sequence:
  std::sregex_token_iterator rend;
  for (; tok_iter!=rend; ++tok_iter) {
    std::string subtoken = *tok_iter;
    //    G4cout << __METHOD_NAME__ << " - subtoken: = <" << subtoken << ">" << G4endl;

    // keep ; ( ) 
    std::regex keep_delimiters("[;\\(\\)]");
    // delimiters (0) and remaining (-1)
    std::sregex_token_iterator tok_iter2(subtoken.begin(), subtoken.end(), keep_delimiters, {-1, 0});

    for (; tok_iter2!=rend; ++tok_iter2) { 
    
      std::string token = *tok_iter2;
      
      RemoveQuotesFromLine(token);
      RemoveWhitespace(token);
      // only put non-empty tokens
      if (!token.empty()) {
	_tokens.push_back(token);
#ifdef BDSDEBUG
	G4cout << __METHOD_NAME__ << " - token: = <" << token << ">" << G4endl;
#endif
      }
    }
  }
  BeginTokens();
}

bool BDSMySQLWrapper::NextToken(){
  std::string line;
  ++_tokens_iter;
  if(_startOfFile){
    --_tokens_iter;
  }
  if(_startOfFile || EndTokens()){
    if(ifs.good()){
      ReadLine();
      TokenizeLine();
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << " - Token() = " << Token() << G4endl;
#endif
    }else{
      return false;
    }
  } else {
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << " - Token() = " << Token() << G4endl;
#endif
  }
  return true;
}



G4int BDSMySQLWrapper::ParseComponent()
{
  // not using these commands yet...
  if(Token()==CMD_DROP) { return 0;}
  else if(Token()==CMD_DATABASE) { return 0;}
  else if(Token()==CMD_IF) { return 0;}
  else if(Token()==CMD_EXISTS) { return 0;}
  else if(Token()==CMD_USE) { return 0;}
  //The following commands are used...
  else if(Token()==CMD_CREATE) {Create(); return 0;}
  else if(Token()==CMD_INSERT) {Insert(); ComponentN++; return 0;}
  return 0;
}


void BDSMySQLWrapper::CreateDatabase(){
}

void BDSMySQLWrapper::CreateTable(){
  G4String varname;
  G4String vartype;

  _NEXTINPUT
    CurrentTableName=Token();
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " reading CurrentTableName: " << CurrentTableName << G4endl;
#endif
  ProceedToEndOfLine();
  table.push_back(new BDSMySQLTable(CurrentTableName));
  tableN++;
  
  while((!varname.contains(";")) && (!vartype.contains(";"))){
    //Get next variable, skipping blanks.
    do{
      _NEXTINPUT
	} while((EmptyToken()) || (EndOfLine()));
    varname=Token();
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << " reading varname: " << varname << G4endl;
#endif
    if (varname.contains(";")) return; //Semicolon indicates end of table.
    _NEXTINPUT
      vartype=Token();
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << " reading vartype: " << vartype << G4endl;
#endif
    if (vartype.contains(";")) return; //Semicolon indicates end of table.
    if(vartype.contains("DOUBLE")) vartype="DOUBLE";
    else if(vartype.contains("VARCHAR")) vartype="STRING";
    else if(vartype.contains("INTEGER")) vartype="INTEGER";
    table[tableN]->AddVariable(varname,vartype);
    ProceedToEndOfLine();
  }
}


void BDSMySQLWrapper::Create(){
  _NEXT
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << " reading input: " << Token() << G4endl;
#endif
  if(Token()==CMD_DATABASE) {CreateDatabase();}
  else if(Token()==CMD_TABLE) {CreateTable();}
}

void BDSMySQLWrapper::Insert(){
  _NEXT
#ifdef BDSDEBUG
    G4cout << __METHOD_NAME__ << " reading input: " << Token() << G4endl;
#endif
  if(Token()==CMD_INTO){InsertInto();}
}

void BDSMySQLWrapper::InsertInto() {
  _NEXT
    InsertTableName=Token();
  _NEXT
    if(Token()==CMD_VALUES){Values();}
}
 
void BDSMySQLWrapper::Values() {
  for(G4int j=0; j<(G4int)table.size(); j++){
    if(table[j]->GetName()==InsertTableName){
      for(G4int k=0; k<table[j]->GetNVariables(); k++){
	_NEXTINPUT
	  //Skip first bracket...
	while (Token()=="(") {
	  _NEXTINPUT
	}
	if (Token()==")") {
	  //	  std::stringstream excptnSstrm;
	  //	  excptnSstrm<<__METHOD_NAME__<< " - expected " << table[j]->GetNVariables() << " values for insertion into table " << InsertTableName << "\n";
	  //	  G4Exception(excptnSstrm.str().c_str(), "-1", FatalException, "");
	  //	  return;
	}
#ifdef BDSDEBUG
	G4cout << __METHOD_NAME__ << " inserting value " << Token() << G4endl;
#endif
	if(table[j]->GetVariable(k)->GetVarType()=="DOUBLE")
	  table[j]->GetVariable(k)->AddValue(atof(Token().c_str())*CLHEP::mm);
	else if(table[j]->GetVariable(k)->GetVarType()=="STRING")
	  table[j]->GetVariable(k)->AddValue(Token().c_str());
	else if(table[j]->GetVariable(k)->GetVarType()=="INTEGER")
	  table[j]->GetVariable(k)->AddValue(atoi(Token().c_str()));
      }
    }
  }
}

void BDSMySQLWrapper::BeginTokens(){
  _tokens_iter=_tokens.begin();
}

bool BDSMySQLWrapper::NextInputToken(){
  if(ifs.good()){
    bool status;
    do{
      status=NextToken();
    } while (EndOfLine());
    return status;
  } else {
    return false;
  }
}

bool BDSMySQLWrapper::EndTokens(){
  return(_tokens_iter==_tokens.end());
}

bool BDSMySQLWrapper::EndOfLine(){
  return((*_tokens_iter)=="\n");
}

bool BDSMySQLWrapper::EmptyToken(){
  return((*_tokens_iter)=="");
}

std::string BDSMySQLWrapper::Token(){
  return *_tokens_iter;
}

void BDSMySQLWrapper::ProceedToEndOfLine(){
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << G4endl;
#endif
  while(!EndOfLine()){
    _NEXT
#ifdef BDSDEBUG
      G4cout << __METHOD_NAME__ << " " << Token() << G4endl;
#endif
  }
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " finished." << G4endl;
#endif
}

void BDSMySQLWrapper::ReadLine(){
  _currentLine.clear();
  _startOfFile=false;
  //returns non zero if unsuccessful
  char buffer[512];
  ifs.getline(buffer,512);
  _currentLine=buffer;
  RemoveCommentsFromLine(_currentLine);
  //Put back the new line character
  _currentLine += ' ';
  _currentLine += '\n';
#ifdef BDSDEBUG
  G4cout << __METHOD_NAME__ << " - _currentLine = " << _currentLine << G4endl;
#endif
}

void BDSMySQLWrapper::RemoveCommentsFromLine(std::string& value){
  //Strip all characters after and including '#'
  unsigned pos = value.find('#');
  std::string uncommented = value.substr(0,pos);
  value=uncommented;
}

void BDSMySQLWrapper::RemoveQuotesFromLine(std::string& value){
  //Strip all "
  value.erase (std::remove(value.begin(), value.end(), '\"'), value.end());
}


void BDSMySQLWrapper::RemoveWhitespace(G4String& val){
  std::string s = val;
  RemoveWhitespace(s);
  val=(G4String)s;
}

void BDSMySQLWrapper::RemoveWhitespace(std::string& val){
  val.erase( std::remove_if( val.begin(), val.end(), ::isblank ), val.end() );
}

/*
void Log(const G4String& tag, int depth, ostream& os)
{
  static const char* tab = "----|";
  while(depth--) os<<tab;
  os<<' '<<tag<<endl;
}
*/




 
