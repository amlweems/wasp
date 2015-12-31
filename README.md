# wasp
Useful if you find code that uses `Random()` in place of a secure source of randomness.

`wasp` can be used to *reverse engineer* the output of the PRNG and determine the value of `Environment.TickCount`.

This can be abused for further mischief.

# Usage

First and foremost, you should review the MSDN documentation of `Random()`. You'll need to create a function that can determine if a particular seed successfully generates your desired output. Place this code within the `Success()` function. Our `Success()` function gives the example of a password generated via letters, numbers, and symbols. Customize the function to fit your needs.

An example run of wasp will go as follows:
```
$ ./wasp <starting seed>
[+] Starting brute force.
[+] Found seed: 1078932773
8932773 seeds tested 5.257142 secs (1699169 seeds/sec)
```

If you have designed your `Success()` function incorrectly, you'll likely find the following output after a considerable time.
```
$ ./wasp <starting seed>
[+] Starting brute force.
[-] Seed not found. :(
4294967296 seeds tested 2526.256680 secs (1700131 seeds/sec)
```
