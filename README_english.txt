/// HOW TO USE (english)

To run the program, you need the Zinjai IDE.

Open the file IdiomasParaSorprender.zrp in the IDE.

Compile and run it directly from Zinjai.

/// ABOUT THE TEXT PROCESSOR

Words are extracted by checking whether the current character
is alphabetical. If so, it is concatenated into a temporary string (word).

However, this approach also causes sequences such as II, III, IV, V, etc.
to be interpreted as words, even though they are actually Roman numerals.
This is just one example, but there are other similar cases.

We implemented a blacklist system,
where each completed word is checked against a predefined list
of invalid terms. If the word is included in this list,
it will not be considered by the rest of the program.

/// ABOUT THE INCLUDED FILES
//FILE usuarios.bin

The binary file usuarios.bin was created using auxiliary code,
located in the extras folder.

Here is a list of sample users that may be useful:

ID: 12348 | Password: 84329 | (Daniel Ambort)

ID: 12350 | Password: 05321 | (Diana Margarita)

ID: 12345 | Password: 54326 | (Scarabino Román)

ID: 12352 | Password: 25323 | (Sophia Davis)

ID: 12361 | Password: 16322 | (Henry Taylor)

//FILE frecuencia.txt

The assignment required following the format of an example file.
However, the example file was not attached in the email.

Although the request was made to obtain the missing reference,
no response was received. If needed, this file can be easily modified
to meet the required format.