## IMPLEMENTATION OF A SIMPLIFIED DES FOR EDUCATIONAL PURPOSES 

## Introduction

Hello, and welcome to my very first GitHub project. As a part of my Master in Computer Science studies, and more precisely my Introduction to Cybersecurity class, we were asked to implement, in whichever language we want, a simplified version of the DES encryption algorithm. This SDES has similar properties and structure to DES, even though it is working with much smaller parameters.
This project required us to code an encryption function and a decryption function.
In order to do so, I followed the instructions written in the PDF file at the root of the project. It is pretty precise, and I'd advise any interested reader to go through it in order to understand
what is going on in this project.

To sum things up in a concise fashion, this implementation works with an 8-bit plaintexts and a 10-bit key (the latter being supposed to be known by both the sender and receiver of a message).
The S_DES encryption function converts this plaintext into an 8-bit ciphertext, using many functions I'll detail throughout this README.

## Why did I choose to implement such an encryption algorithm using C, out of the many programming languages?

Excellent question. The reason is pretty simple: it is, as of right now, the language I'm the most knowledgeable in. Moreover, the deadline set for this project was pretty short, and even though I could have done it in Java/C++ (which would have been ever so useful as it would have been easier to work with bitwise structures and operations), I decided to code everything in C.
This was an extremely fun and interesting project, as I learned many things regarding bitwise operations.


## What are the problems I encountered throughout the implementation of this algorithm?

The first problem was finding the right data structures to work with, as C doesn't have any binary types per se (contrary to other languages). Our instructions were pretty vague, so I decided to use the u_int8_t and u_int16_t structures to represent respectively the 8-bit words and 10-bit words.
In hindsight, this was the major problem I encountered. I hadn't worked with bitwise operations before this very project (or very little), so it took me a day to get accustomed to everything, but I got the gist of it, and managed to produce effective (and working) functions.


### Yes, very interesting, but how does it actually work?

I'm getting to it, curious reader, do not worry. In order to not fall into redundancy, and as I commented my code with many details, I will not explain everything, but the outlines of this project.


## The encryption function


The S_DES encryption function can be described as follows: it requires an 8-bit plaintext along with a 10-bit key as parameters, and produces an 8-bit ciphertext. But how does it produce it, one may ask? This function is a composition of five functions: 
> Ciphextext = IP⁻¹ $fk_{1}$



