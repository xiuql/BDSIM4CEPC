#ifndef __SYM_TABLE_H
#define __SYM_TABLE_H

#include <list>
#include <string>

namespace GMAD {
  /** 
      @brief Common header for the lexer and the parser 
      to share Symbol table for numeric variables and functions
  */
  class Array;
  
  class Symtab {
  public:
    /// Symtabs and arrays are kind of interchangeable
    friend class Array;

    enum class symtabtype {
      NUMBER=0,
      STRING=1,
      ARRAY=2,
      FUNCTION=3
    };
    /// typedef for function pointer
    typedef double (*function)(double);

  public:
    /// Constructor with name
    explicit Symtab(std::string s);
    /// Set to Array value
    void Set(Array*);
    /// Set to string
    void Set(std::string);
    /// Set to double, optional argument to reserve name (only used for units for now)
    void Set(double,bool reserved=false);
    /// Set to function pointer
    void Set(function);

    /// Get name
    std::string GetName()const;
    /// Get type
    symtabtype GetType()const;
    /// Check if symbol is a reserved name
    bool IsReserved()const;
    /// Get methods that check on type
    std::list<double> GetArray()const;
    /// Set to string
    std::string GetString()const;
    /// Set to double
    double GetNumber()const;
    /// Set to function pointer
    function GetFunction()const;

    /// Print method
    void Print();

  private:
    /// Name of parser symbol
    std::string name;
    /// Flag is parser symbol is a reserved name
    bool is_reserved;
    /// Enum type 
    symtabtype type;
    ///@{ data
    function funcptr;
    double value;
    std::string str;
    std::list<double> array;
    ///@}

  };
}

#endif
