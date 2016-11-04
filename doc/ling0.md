Ling0 {#mainpage}
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

Syntax
------

<table class="ebnf" border=1>
<caption>Ebnf-like</caption>
<tr><th>Rule                </th><th> Definition </th></tr> 
<tr><td>Module              <td> [("module"|"program"), qualified-id, ";"], declarations ; 
<tr><td>declarations        <td> {section, ":"}, commands ;
<tr><td>section             <td> "public" | "private" ;
<tr><td>commands            <td> command % ";", [";"] ;
<tr><td>command             <td> binding
                            <br/> | import
                            <br/> | function definition
                            <br/> | type definition
                            <br/> | return
                            <br/> | expression
<tr><td>binding             <td> "let", ["mutable"], id, binding init;
<tr><td>binding init        <td> ":", type declaration ["=", expression] | "=", expression;
<tr><td>import              <td> "import", qualified-id, ["as", id];
<tr><td>function definition <td> "def", id, [function signature], "{", commands, "}" ;
<tr><td>function signature  <td> "(", (id, ":", type declaration) % ",", ")", [":", type declaration] ;
<tr><td>type definition     <td> struct definition | union definition | impl definition | trait definition | trait specialization;
<tr><td>struct definition   <td> "struct", id, composed definition;
<tr><td>union definition    <td> "union", id, composed definition;
<tr><td>composed definition <td> "{", (id, ":", type declaration % ","), [","] "}";
<tr><td>impl definition     <td> "impl", id, "{", {method definition % ","}, "}",
<tr><td>expression          <td> {lhs, "="}, rhs;
<tr><td>rhs                 <td> logical expression | "if", logical expression, "then", rhs, "else", rhs;
<tr><td>lhs                 <td> qualified-id;
<tr><td>logical expression  <td> comp expression % ("and" | "or");
<tr><td>comp expression     <td> infix expression % ("=="| "!="| "<"| ">"| "<="| ">=");
<tr><td>infix expression    <td> sum expression, [infix-op, ((sum expression | call) % infix-op)];
<tr><td>infix-op            <td> "|", id, "|";
<tr><td>sum expression      <td> mul expression % ("+" | "-");
<tr><td>mul expression      <td> prefix expression % ("*" | "/" | "%");
<tr><td>prefix expression   <td> {"not" | "-"}, posfix expression;
<tr><td>posfix expression   <td> leaf expression, {call | dot expression}
<tr><td>leaf expression     <td> id | "(", expression, ")" | numeric constant | string constant | sequence constant | associative constant;
<tr><td>sequence constant   <td> "[", (expression % ","), "]";
<tr><td>associative constant<td> "{", ([(id | "(", expression, ")"), "="], expression), "}";
<!-- -->
<tr><td>qualified-id        <td> id, {dot expression};
<tr><td>dot expression      <td> ".", id;
<!-- -->
<tr><td>type declaration    <td> id, [ "<", (type declaration | numeric constant | string constant % ",") , ">"]
</table>

