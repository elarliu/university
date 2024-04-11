#include "lex.hpp"

// TW - таблица служебных слов
// TD - таблица ограничителей
// TID - таблица идентификаторов анализируемой программы

std::ostream & operator << (std::ostream & s, Lex l ) 
{
    s << '(' << l.t_lex << ',' << l.v_lex << ",\"" << l.n_lex << "\");" ;
    return s;
}

std::string Scanner::TW [] = 
{   
    "NULL", "NOT", "AND", "OR", "SELECT", "INSERT",
    "UPDATE", "DELETE", "CREATE", "DROP", "INTO", "WHERE", 
    "LONG", "ALL", "TEXT", "LIKE", "TRUE", "FALSE", 
    "LOGIC", "TABLE", "FROM", "IN", "SET", "EXIT", "#"
};

std::string Scanner::TD[] = 
{   
    "NULL", "\'", ",", "(", ")", "[", "]", 
    "=", "<", ">", "+", "-", "*",
    "/", "<=", "!=", ">=", "%"
};

int put(const std::string & buf)
{
    std::vector<Ident>::iterator k;

    if((k = std::find(TID.begin(), TID.end(), buf)) != TID.end())
        return k - TID.begin();
    
    TID.push_back(buf);
    return TID.size() - 1;
}

Lex Scanner::get_lex()
{
    enum state { 
        H,          
        IDENT,          // идентификатор
        NUMB,           // число
        COM,            // комментарий
        ALE,            // > < >= <=
        NEQ,            // !=
        LETTER          // string
        // квадратные скобочки и like ??
        };
    int d, j, sign_flag = 1;
    std::string buf;
    state CS = H;
    do
    {
        gc();
        switch (CS)
        {
        case H:
            if (c == ' ' || c == '\n' || c == '\r' || c == '\t');
            else if (isalpha(c))
            {
                buf.push_back(c);
                CS = IDENT;
            }
            else if (isdigit(c))
            {
                d = c - '0';
                CS = NUMB;
            }
            else if(c == '-')
            { 
                sign_flag = -1;
                j = look(buf, TD, TDlen);
                return Lex(LEX_MINUS, j, "-");
                // break;
            }
            else if (c == '#')
            {
                CS = COM;
            }
            else if (c == '>' || c == '<' || c == '=')
            {
                buf.push_back(c);
                CS = ALE;
            }
            else if (c == '!')
            {
                buf.push_back(c);
                CS = NEQ;
            }
            else if (c == '\'')
            { 
                CS = LETTER;
            }
            else 
            { 
                buf.push_back(c);
                if(j = look(buf, TD, TDlen))
                {
                    return Lex((type_of_lex) (j - 1 + (int) LEX_EXIT), j, buf);
                }
                else 
                    throw c;
            }
            break;
        case IDENT:
            if(isalpha(c) || isdigit(c) || c == '_')
            {
                    buf.push_back(c); 
            }
            break;
        default:
            break;
        }
    } while (true);
    
}