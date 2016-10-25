Ling0.md
========

A small language experiment. We want to be able make a language with semantics close to C, C++,
with a very simple syntax, but with modern facilities, like a sane module system, a unambiguous
parsing way, sum types, etc.

Our code should be compilable to a C++ program, with C-89 ABI.

Type system
-----------
The type system is static, with ability to delay it to runtime. We have a number of base types, called atoms,
like basic numeric types, boolean and the string reference. The atom types are given by the implementation.
It shoud have at least:

- Int: Any signed integer numeral, within a implementation defined range of at least +-(2 |pow| 64)
- Float: Any floating float point number, implementation defined.
- Boolean: True/On/1 or False/Off/0
- CharSeq: A Const Imutable character reference.
- Dyn: Dynamic fetched type. The compiler delay all checking to runtime.

Over that ones you can edit/combine them in multiple ways:
- Struct: A new type that combine other types. `struct<Type1, Type2 ...>`
- Arraying: Multiple values of same type `array<N>`;
- Union: A discriminated union over multiple types `union {Type1, Type2 ...}`;
- Ref: A indirect reference to a value. The reference must be guaranted to not outlive the referenced `ref<TYPE>`.
- Pointer: A indirect reference owned `pointer<TYPE>`.
- Shared reference: A indirect reference to a value owned by a shared pointer
- Shared Pointer: A indirect reference that owns the pointer collectivelly (through reference counting)
- Mul: Implicit applied to binding marked as multable.
- Function: Combines an in type, an out type and a context. `def<IN, OUT, CONTEXT>`.

Other basic types are actually part of the lib.
- Type: A type referecing other types
- String: A String

Security
--------
Like Rust, some operations are executable only in functions/regions marked as unsafe.

Module system
-------------
The module system is a simple with transitive dependencies organized as a DAG. Modules also can have a
sub modules. A parent sees all its submodules and can depend upon siblings, A submodule can also be referred directly.

Modules can have kinds, some predefined and some are custom.

```ebnf
Module              = ["module", qualified-id, ";"], declarations ;
declarations        = {section, ":"}, commands ;
section             = "public" | "private" ;
commands            = command % ";", [";"] ;
commands            = binding
                    | import
                    | function definition
                    | type definition
                    | return
                    | expression
binding             = "let", ["mutable"], id, binding init;
binding init        = ":", type declaration ["=", expression] | "=", expression;
import              = "import", qualified-id, ["as", id];
function definition = "def", id, [function signature], "{", commands, "}" ;
function signature  = "(", (id, ":", type declaration) % ",", ")", [":", type declaration] ;
type definition     = struct definition | union definition | impl definition | trait definition | trait specialization;
struct definition   = "struct", id, composed definition;
union definition    = "union", id, composed definition;
composed definition = "{", (id, ":", type declaration % ","), [","] "}";
impl definition     = "impl", id, "{", {method definition % ","}, "}",

expression          = {lhs, "="}, rhs;
rhs                 = logical expression | "if", logical expression, "then", rhs, "else", rhs;
lhs                 = qualified-id;
logical expression  = comp expression % ("and" | "or");
comp expression     = infix expression % ("=="| "!="| "<"| ">"| "<="| ">=");
infix expression    = sum expression, [infix-op, ((sum expression | call) % infix-op)];
infix-op            = "|", id, "|";
sum expression      = mul expression % ("+" | "-");
mul expression      = prefix expression % ("*" | "/" | "%");
prefix expression   = {"not" | "-"}, posfix expression;
posfix expression   = leaf expression, {call | dot expression}
leaf expression     = id | "(", expression, ")" | numeric constant | string constant | sequence constant | associative constant;
sequence constant   = "[", (expression % ","), "]";
associative constant= "{", ([(id | "(", expression, ")"), "="], expression), "}";

qualified-id        = id, {dot expression};
dot expression      = ".", id;

type declaration    = id, [ "<", (type declaration | numeric constant | string constant % ",") , ">"]
```
