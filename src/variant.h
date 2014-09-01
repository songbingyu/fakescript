#pragma once

#include "types.h"

class Variant 
{
public:

	enum Type 
	{
		NIL,		
		
		// atomic types 		
		BOOL,
		INT,
		REAL,
		STRING,

		// pointer
		POINTER,
		
		VARIANT_MAX
	};	
    
    
	Variant(const Variant& p_variant);
	Variant() { m_type = NIL; }
	~Variant() { if (m_type != Variant::NIL) clear(); }

	Variant(bool p_bool);
	Variant(signed int p_int); // real one
	Variant(unsigned int p_int);
	Variant(signed short p_short); // real one
	Variant(unsigned short p_short);
	Variant(signed char p_char); // real one
	Variant(unsigned char p_char);
	Variant(int64_t p_char); // real one
	Variant(uint64_t p_char);
	Variant(float p_float);
	Variant(double p_double);
	Variant(const String& p_string);
	Variant(const char * const p_cstring);
	Variant(void * p_ptr);
	
	bool operator==(const Variant& p_variant) const;	
	void operator=(const Variant& p_variant); // only this is enough for all the other types
	
	operator bool() const;
	operator signed int() const;
	operator unsigned int() const; // this is the real one
	operator signed short() const;
	operator unsigned short() const;
	operator signed char() const;
	operator unsigned char() const;
	//operator long unsigned int() const;
	operator int64_t() const;
	operator uint64_t() const;
	operator signed long() const;
	operator unsigned long() const;
	operator float() const;
	operator double() const;
	operator String() const;

	Type get_type() const { return m_type; }
	static String get_type_name(Variant::Type p_type);
	static bool can_convert(Type p_type_from,Type p_type_to);

	template<class T>
	static Type get_type_for() {
		
		GetSimpleType<T> t;
		Variant v(t.m_type);
		return v.get_type();
	}

	bool is_ref() const { return m_type == POINTER; }
	bool is_num() const { return m_type == INT || m_type == REAL; };
	bool is_shared() const;
	bool is_zero() const;

	uint32_t hash() const;

	bool booleanize() const;

private:

	union MemData
	{
		bool m_bool;
		int64_t m_int;
		double m_real;
		String * m_str;
		void * m_ptr; //generic pointer
	};

	void reference(const Variant& p_variant);
	void clear();
	
private:

	Type m_type;

	MemData m_data;
};

