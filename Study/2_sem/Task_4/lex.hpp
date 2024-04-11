#ifndef LEX_HPP
#define LEX_HPP

#include <iostream>
#include <string>
#include <vector>

#define TWlen 24
#define TDlen 18

enum type_of_lex
{
    LEX_NULL,           // 0 nullptr
    LEX_NOT,            // 1 not
    LEX_AND,            // 2 &&
    LEX_OR,             // 3 ||
    LEX_SELECT,         // 4 SELECT
    LEX_INSERT,         // 5 INSERT
    LEX_UPDATE,         // 6 UPDATE
    LEX_DELETE,         // 7 DELETE
    LEX_CREATE,         // 8 CREATE
    LEX_DROP,           // 9 DROP
    LEX_INTO,           // 10 INTO
    LEX_WHERE,          // 11 WHERE
    LEX_LONG,           // 12 LONG
    LEX_ALL,            // 13 ALL
    LEX_TEXT,           // 14 TEXT
    LEX_LIKE,           // 15 LIKE
    LEX_TRUE,           // 16 TRUE
    LEX_FALSE,          // 17 FALSE
    LEX_LOGIC,          // 18 LOGIC
    LEX_TABLE,          // 19 TABLE
    LEX_FROM,           // 20 FROM
    LEX_IN,             // 21 IN
    LEX_SET,            // 22 SET
    LEX_EXIT,           // 23 EXIT
    LEX_XOR,            // 24 ^
    LEX_COMMA,          // 25 , 
    LEX_RND_BRCKT_O,    // 26 (
    LEX_RND_BRCKT_C,    // 27 )
    LEX_SQR_BRCKT_O,    // 28 [
    LEX_SQR_BRCKT_C,    // 29 ]
    LEX_EQ,             // 30 =
    LEX_LSS,            // 31 <
    LEX_GTR,            // 32 >
    LEX_PLUS,           // 33 +
    LEX_MINUS,          // 34 -
    LEX_TIMES,          // 35 *
    LEX_SLASH,          // 36 /
    LEX_LEQ,            // 37 <=
    LEX_NEQ,            // 38 !=
    LEX_GEQ,            // 39 >=
    LEX_MOD,            // 40 %
    LEX_COMMENT,        // 41 #
    LEX_ALLCOLS,        // 42 * (в таблице)
    LEX_UNMINUS,        // 43 - (унарный)
    LEX_NUM,            // 44 число
    LEX_ID,             // 45 идентификатор
    LEX_UNDER,          // 46 нижнее подчеркивание
    LEX_LETTER,         // 47 сообщение в кавычках
    POLIZ_SENTENCE,     // 48 конец SQL-предложения
};

class Lex
{
    public:
        Lex(type_of_lex t = LEX_NULL, int v = 0, const std::string & n = ""): t_lex(t), v_lex(v) 
        {
            n_lex = n;
        }

        type_of_lex get_type() {return t_lex;}
        int get_value() {return v_lex;}
        std::string get_string() {return n_lex;}

        friend std::ostream & operator << (std::ostream & out, Lex l);

    private:
        type_of_lex t_lex;
        int v_lex;
        std::string n_lex;
};

class Ident
{
    public:
        Ident()
        {
            declare = false;
            assign = false;
        }

        Ident(const std::string & n)
        {
            name = n;
            declare = false;
            assign = false;
        }

        bool operator == (const std::string & n) { return name == n; }
        std::string get_name() { return name; }

        bool get_declare() const { return declare; }
        void put_declare() { declare = true; }

        type_of_lex get_type() const { return type; }
        void put_type(type_of_lex t){ type = t; }

        bool get_assign() const { return assign; }
        void put_assign(){ assign = true; }

        int get_value() const { return value; }
        void put_value(int v) { value = v; }

    private:
        std::string name;
        bool declare;
        type_of_lex type;
        bool assign;
        int value;
};

std::vector<Ident> TID;

// TID
int put(const std::string & buf);

class Scanner 
{
    public:
        static std::string TW [], TD [];
        Scanner ( const char * program ) 
        {
            if ( !(fp = fopen ( program, "r" )) ) 
                throw  "can't open file" ;
        }
        Lex get_lex();
    private:
        FILE * fp;
        char   c;
        int look(const std::string buf, std::string * list, int n) 
        {
            int i = 0;
            while (i < n) 
            {
                if (buf == list[i])
                {
                    return i;
                }
                i++; 
            }
            return 0; 
        }
        void gc () 
        {
            c = fgetc(fp);
        }
};

#endif