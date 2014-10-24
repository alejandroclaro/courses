#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

class VariableNode
{
  public:

    VariableNode(Symbol name, Symbol type)
    : m_name(name)
    , m_type(type)
    {      
    }

  private:

    Symbol m_name;
    Symbol m_type;
};

class ClassNode
{
  public:

	  ClassNode(Class_ klass)
    : m_klass(klass)
    {      
    }

	  Method find_method(Symbol name);
	  bool is_subclass_of(Symbol name);

    void check(SymbolTable<Symbol, ClassNode>* classes, SymbolTable<Symbol, VariableNode>* variables);

  private:

	  Class_ m_klass;
};

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.
class ClassTable
{
  private:
  
    int semant_errors;
    ostream& error_stream;
	  SymbolTable<Symbol, ClassNode>    classes_table;
    SymbolTable<Symbol, VariableNode> variables_table;

    void install_basic_classes();
    bool check_parent(Class_ current);

  public:
  
  ClassTable(Classes);
  
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
};

#endif
