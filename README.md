# Anti-CrackMe-V2 Source Code

Here i Will Explain How The App Encrypting The Password Step By Step:-

1.The App Will Get The Username string Then Reversing It
2.Then The App Is Going To Preform Simple Caesar Cipher For The Reversed String:-
If Char Is Capital Letter The Shift Will Be 9 times / If Char Is Small Letter The Shift Will Be 14 times / If Char Is Number The Shift Will Be 4 times
3.Then Its Going To Convert The String To Binary
4.Then Its Going To Reverse The Binary Result
5.The Last Step Is Shifting 0 to 1 and 1 to 0 of every last 4 chars of the binary: 011000010110001001100011 -> 011011100110110101101100
                                                                                       ^^^^    ^^^^    ^^^^
