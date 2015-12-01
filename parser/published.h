#ifndef __PUBLISH_H
#define __PUBLISH_H

#include <list>
#include <string>
#include <unordered_map>

namespace GMAD
{
  /** 
   * @brief Class that provides introspection to its members
   *
   * In the parser the keywords in the ASCII files need to be matched to the correct member variable.
   * However, C++ has no introspection ability. This class provides this artificially.
   * 
   * All members need to be added explicitly to a hash table (unordered_map) with the method publish.
   * Note that the name can be different from the actual member name
   * 
   * adapted into a class from http://stackoverflow.com/questions/19557881/convert-string-character-to-class-member-method-in-c
   *
   * @author Jochem Snuverink <Jochem.Snuverink@rhul.ac.uk>
   */

  template<typename C>
    class Published
    {
    protected:
      /// Make pointer to member from class C and type T with accessible with a name
      template<typename T>
	void publish(const std::string& name, T C::*mp);
      ///@{
      /// Set member with name of class instance to value.
      /// Throws std::runtime_error if not found
      void set(C* instance, const std::string& name, double value);
      template<typename T>
	void set(C* instance, const std::string& name, const T& value);
      ///@}

      /// Set member with name of class instance to value of second instance
      void set(C* instance, const C* instance2, const std::string& name);
      
      /// Define AttributeMap of string and class member pointer
      template <typename T>
	using AttributeMap = typename std::unordered_map<std::string, T C::*>;
      
      /// Access method to static map for type T and class C
      template <typename T>
       	AttributeMap<T>& attribute_map() const;

      template <typename T>
	T get(const C* instance, const std::string& name) const;
      
    private:
      /// Access to member pointer
      template<typename T>
	T C::* member(const std::string& name) const;
    };

  // implementation for templated class needs to be in header
  
  template<typename C>
    template<typename T>
    void Published<C>::publish(const std::string& name, T C::*mp)
    {
      attribute_map<T>()[name] = mp;
    }

  template<typename C>
    void Published<C>::set(C* instance, const std::string& name, double value)
    {
      // check maps for double, int, bool
      // tried to do this more general (e.g. with a single map),
      // but difficult since member pointers have different types
      // better would be to keep a list of arithmetic types published and loop over those
      try {
	double C::* mp = member<double>(name);
	(instance)->*mp = value;
      }
      catch (std::runtime_error) {
	try {
	  int C::* mp = member<int>(name);
	  (instance)->*mp = value;
	}
	catch (std::runtime_error) {
	  try {
	    bool C::* mp = member<bool>(name);
	    (instance)->*mp = value;
	  }
	  catch (std::runtime_error) {
	    // if not found throw error
	    throw std::runtime_error("Unknown member " + name);
	  }
	}
      }
    }

  template<typename C>
    template<typename T>
    void Published<C>::set(C* instance, const std::string& name, const T& value)
    {
      try {
	T C::* mp = member<T>(name);
	(instance)->*mp = value;
      }
      catch (std::runtime_error) {
	// if not found throw error
	throw std::runtime_error("Unknown member " + name);
      }
    }

  template<typename C>
    void Published<C>::set(C* instance, const C* instance2, const std::string& name)
    {
      // unfortunately, have to try all existing types
      try {
	// pointer to member
	double C::* mp = member<double>(name);
	// set value
	(instance)->*mp = (instance2)->*mp;
      }
      catch (std::runtime_error) {
	try {
	  int C::* mp = member<int>(name);
	  (instance)->*mp = (instance2)->*mp;
	}
	catch (std::runtime_error) {
	  try {
	    bool C::* mp = member<bool>(name);
	    (instance)->*mp = (instance2)->*mp;
	  }
	  catch (std::runtime_error) {
	    try {
	      std::string C::* mp = member<std::string>(name);
	      (instance)->*mp = (instance2)->*mp;
	    }
	    catch (std::runtime_error) {
	      try {
		std::list<std::string> C::* mp = member<std::list<std::string>>(name);
		(instance)->*mp = (instance2)->*mp;
	      }
	      catch (std::runtime_error) {
		try {
		  std::list<int> C::* mp = member<std::list<int>>(name);
		  (instance)->*mp = (instance2)->*mp;
		}
		catch (std::runtime_error) {
		  try {
		    std::list<double> C::* mp = member<std::list<double>>(name);
		    (instance)->*mp = (instance2)->*mp;
		  }
		  catch (std::runtime_error) {
		    // if not found throw error
		    throw std::runtime_error("Unknown member " + name);
		  }
		}
	      }
	    }
	  }
	}
      }
    }

  template <typename C>
    template <typename T>
    T Published<C>::get(const C* instance, const std::string& name) const
    {
      // pointer to member
      T C::* mp = member<T>(name);
      return (instance)->*mp;
    }
  
  template<typename C>
    template<typename T>
    T C::* Published<C>::member(const std::string& name) const
    {
      AttributeMap<T>& m = attribute_map<T>();
      typename AttributeMap<T>::const_iterator it=m.find(name);
      if (it == m.end()) {
	// if not found throw error
	throw std::runtime_error("Unknown member " + name);
      } else {
	return it->second;
      }
    }

  template<typename C>
    template<typename T>
    typename Published<C>::template AttributeMap<T>& Published<C>::attribute_map() const
    {
      // static initialisation for flexibility
      static AttributeMap<T> m;
      return m;
    }
}

#endif
