#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V){}

void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }
string Sym::head() { return tag+":"+val; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S += '\t'; return S; }

Sym* Sym::eval(Sym*E) { return this; }

Str::Str(string V):Sym("str",V){}

Num::Num(string V):Sym("num",V){}

Vector::Vector():Sym("vector","[]"){}

Op::Op(string V):Sym("op",V){}

Env* glob = new Env("global");
Env::Env(string V):Sym("env",V){}
