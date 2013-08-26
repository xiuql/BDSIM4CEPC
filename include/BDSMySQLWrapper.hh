/* * BDSIM code.    Version 1.0
   * Author: Grahame A. Blair, Royal Holloway, Univ. of London.
   * Last modified 24.7.2002
   * Copyright (c) 2002 by G.A.Blair.  ALL RIGHTS RESERVED. 


   Author of this code: John C. Carter, Royal Holloway, Univ. of London.
   Last modified 12.10.2005
*/


#ifndef BDSMySQLWrapper_h
#define BDSMySQLWrapper_h 1

#include "BDSAcceleratorComponent.hh"
#include "BDSMySQLTable.hh"
#include <fstream>
#include <vector>
#include <string>

#define  _NEXT if(!NextToken()) return;
#define  _NEXTINPUT if(!NextInputToken()) return;
#define CMD_CREATE   "CREATE"
#define CMD_TABLE    "TABLE"
#define CMD_INSERT   "INSERT"
#define CMD_INTO     "INTO"
#define CMD_VALUES   "VALUES"
#define CMD_DROP     "DROP"
#define CMD_DATABASE "DATABASE"
#define CMD_USE      "USE"
#define CMD_IF       "IF"
#define CMD_EXISTS   "EXISTS"

using namespace std;

class BDSMySQLWrapper 
{
public:
  BDSMySQLWrapper (const G4String& SQLFileName);
  ~BDSMySQLWrapper();
  
  vector<BDSMySQLTable*> ConstructTable();

  G4int GetComponentN() {return ComponentN;}
 
  vector<BDSMySQLTable*> table;

protected:
  
private:
  // Data Members for Class Attributes

  ifstream ifs;
  
  G4String CurrentTableName;
  G4String InsertTableName;
  G4int ComponentN;

  G4int tableN;

  bool ReadLine(string&);
  void RemoveCommentsFromLine(string& value);
  void RemoveQuotesFromLine(string& value);
  void RemoveWhitespace(std::string&);
  void RemoveWhitespace(G4String&);
  void TokenizeFile();
  vector<string> _tokens;
  vector<string>::iterator _tokens_iter;

  void BeginTokens();
  bool NextToken();
  bool NextInputToken();
  bool EndTokens();
  string Token();
  bool EndOfLine();
  bool EmptyToken();
  void ProceedToEndOfLine();
  G4int ParseComponent();
  //Methods for carrying out the various instructions:
  void Create();
  void CreateDatabase();
  void CreateTable();
  void Insert();
  void InsertInto();
  void Values();


  
};

#endif
