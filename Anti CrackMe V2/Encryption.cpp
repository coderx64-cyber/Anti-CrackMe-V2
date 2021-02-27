#include "Encryption.h"

string CaesarCipher(string text)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]))
            result += char(int(text[i] + 9 - 65) % 26 + 65);

        else if (text[i] > 47 && text[i] < 58)
            result += char(int(text[i] + 4 - 48) % 10 + 48);

        else
            if (int(text[i] < 97 || text[i] > 122))
            {
                cout << "Please Dont Use Special Chars Like : ! + - / *" << "\n" << "The App Will Shutdown!" << "\n";
                system("pause");
                exit(0);
            }
            else
                result += char(int(text[i] + 14 - 97) % 26 + 97);
    }

    return result;
}

string asciiEncryption(string text)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        result += char(int(text[i] + 50 - 33) % 94 + 33);
    }

    return result;
}

string BinaryCipher(string text)
{
    string binaryString = "";
    for (char& _char : text)
    {
        binaryString += bitset<8>(_char).to_string();
    }
    return binaryString;
}

string reverseStr(string text)
{
    string result = "";
    reverse(text.begin(), text.end());
    result = text;
    return result;
}

string ShiftString(string TargetString)
{
    int math = 0, charNum = 4;
    string result = TargetString;

    for (int i = 0; i < TargetString.length(); i++)
    {
        math++;

        if (math == 8)
        {
            for (int i = 0; i < 4; i++)
            {
                if (result[charNum] == '1')
                    result[charNum] = '0';
                else
                    result[charNum] = '1';
                charNum++;
            }

            charNum += 4;
            math = 0;
        }
    }

    return result;
}

string SecondEncrypt(string TargetString)
{
    string ReversedString, ShiftedString;

    ReversedString = reverseStr(TargetString);
    ShiftedString = ShiftString(ReversedString);

    return ShiftedString;
}

string Encrypt(string UnEncryptedString)
{
    string ReversedUser, CaesarUsername, asciiUsername, BinUsername, result;

    ReversedUser = reverseStr(UnEncryptedString);
    CaesarUsername = CaesarCipher(ReversedUser);
    asciiUsername = asciiEncryption(CaesarUsername);
    BinUsername = BinaryCipher(asciiUsername);
    result = SecondEncrypt(BinUsername);

    return result;
}