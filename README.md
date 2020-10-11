<h1 align="center">
  :blue_car: The Korean Tolls Problem
</h1>

- **Project proposed by:** [OB, 2002](https://www.urionlinejudge.com.br/judge/pt/problems/view/2230#:~:text=Como%20pr%C3%AAmio%20pela%20primeira%20coloca%C3%A7%C3%A3o,pai%20de%20Juquinha%2C%20o%20Sr)
- **Project developed by:** [Julio L. Muller](https://github.com/juliolmuller)
- **Released on:** Sep 11, 2020
- **Updated on:** Sep 11, 2020
- **Latest version:** 1.0.0
- **License:** MIT

The main objective of this project is to develop a solution in C language to the **Korean Tools Problem** using the *graph* data structure. This was based on the 2002 edition of the [Olimpíada Brasileira de Informática](https://www.urionlinejudge.com.br/judge/pt/problems/view/2230#:~:text=Como%20pr%C3%AAmio%20pela%20primeira%20coloca%C3%A7%C3%A3o,pai%20de%20Juquinha%2C%20o%20Sr.) (Brazilian Computer Olympics).

As award for winning the Brazilian Computer Olympics, Jimmy and his family received a one-week trip to South Korea. As the country is stunning, with traditions, culture, architecture and cuisine very different from Brazilian's (where I'm from), Jimmy's father, Mr. James, decided to rent a car to get to know the country better.

The roads are very well looked after. All are two-way, and two cities can be connected directly by more than one road. However, a fixed toll is payable on all roads (there is a toll in each direction between two cities). As Mr. James doesn't have much money to spend, travel with the car must be very well planned.

We must write a program that, knowing the existing cities and roads in the country, and the city where Jimmy and his family currently are, find each city (other than the city where they are) that they can visit, given the restriction that Mr. James wishes to pay a maximum of **P** tolls.

The input consists of several test sets. The first line of a test set contains four integers **C**, **E**, **L** and **P**. The values **C** and **E** respectively indicate the number of cities and the number of existing roads. The cities are identified by integers from 1 to **C**. The values **L** and **P** indicate, respectively, the city where the Jimmy's family is at the moment and the maximum number of tolls that Mr. James is willing to pay. The following **E** lines each contain the information for a road, represented by a pair of positive integers **X** and **Y**, indicating that there is a (two-way) road from city **X** to city **Y**. The end of the entry is indicated by `C = E = L = P = 0`.

For each test set in the input the program should produce three lines as output. The first line must contain an identifier for the test set, in the format "`Test n`", where `n` is numbered starting at 1. On the second line must appear the identifiers of the cities that can be reached, in ascending order, separated by at least a blank space. The third line must be left blank. The spelling shown in the Output Example, below, must be followed strictly.

A step-by-step of the logical reasoning for building the program is available in [this presentation](./presentation.ppsx) (pt-BR).

### Restrictions

* 0 <= C <= 50 (C = 0 only on input end)
* 0 <= E <= 2500 (E = 0 only on input end)
* 0 <= L <= C (L = 0 only on input end)
* 0 <= P <= C (P = 0 only on input end)
* 1 <= X <= C
* 1 <= Y <= C

### Example

```bash
# Input:
5 4 2 1
1 2
2 3
3 4
4 5
9 12 1 2
2 1
1 5
2 1
3 2
9 3
3 4
4 8
4 7
7 6
5 6
4 5
3 7
0 0 0 0

#Output
Test 1
1 3

Test 2
2 3 4 5 6
```

## :trophy: Lessons Learned

- **Graph** data structure; and
- Graph data structure using **adjacency matrix**.

## :hammer: Technologies & Resources

- *C* language
- Minimalist GNU for Windows

## :bell: Compiling and Running the Program

To execute the program, first you need to compile its source code using a **C compiler**. As I am on Windows, I'm using *[MinGW](http://www.mingw.org/)* that allows me to use `gcc` for compilation:

```bash
# Compiles the application to "tolls.exe"
$ gcc tolls.c -o tolls

# Run the application
$ tolls

# Run the application using files as standard input
$ tolls < test.txt
```
