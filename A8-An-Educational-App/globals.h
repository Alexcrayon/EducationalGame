#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <map>
#include <QObject>
#include <QString>
#include <QIcon>

using std::vector;
using std::map;

struct Upgrade {
    QString name;
    int id;
    QString description;
    QString prosDescription;
    QString consDescription;
    QString upgradeTowerDescription;
    QString funSecurityFact;
    int complexityLevel; // 0 is least complex, 3 most complex; four upgrade per complexity level
    double damageIncrease;
    double rangeIncrease;
    double lifeIncrease;
    double cost;
    QString icon;
};

const static struct Upgrade length = {
    "Increase Length",
    0,
    "Increase the length of the password.",
    "A longer password makes it more difficult for an adversary to crack by brute force since the number of possible combinations"
    " increases exponentially. For example, a password that only uses lowercase letters and has length 8 yields 26^8 = 208,000,000,000 possibilities while "
    "simply increasing this to a length of 12 yields 26^12 = 10,000,000,000,000,000 possibilities. Generally, the longer the password the more secure.",
    "A long password won't stop it from being compromised if a breached server stores it in plain text. Also the longer the password the more "
    "difficult it can be to remember. ",
    "Increases tower range",
    "A statistical analysis of over 265 million unique passwords founds that the average length was about 9 characters. ",
    0,
    0,
    15,
    1,
    30,
    ":/File/GameResources/upgradeIcons/length.png"
};

const static struct Upgrade symbols = {
    "Add Symbols",
    1,
    "Add Symbols to the password. Symbols like !, $, &, %, ?, and # appended to the end of the current password",
    "Having symbols or special characters in a password will generally make it more secure against brute for attacks. This is because "
    "the search space of possible characters increase. For example, take a password that only uses lowercase letters and has length 8, there "
    "will be 26^8 = 208,000,000,000 total possibiliies but If we allow for six different special charactkers like !, $, #, %, ?, and & there will "
    "be a total of 32^8 = 1,000,000,000,000. ",
    "Some services may not allow special character / symbols to be included in a password or they may limit it to only a couple symbols. A password "
    "with symbols can also make it more difficult for a user to remember. Additionally, if a server stores passwords without hashing then no amount "
    "of symbols will stop your password from being compromised.",
    "Increases tower damage",
    "An Analysis of Sony and Gawker breached passwords shows that there a 0.4% percent change a password will contain one or more symbols "
    "chance that it contains a symbol or special character and will mostly likely appear at the end of the password.",
    0,
    5,
    0,
    2,
    30,
    ":/File/GameResources/upgradeIcons/symbols.png"
};

const struct Upgrade numbers = {
    "Add Numbers",
    2,
    "Adding a few numbers to the end of the password",
    "Having numbers in a password can make it more secure against brute for attacsk for two main reasons. One it increases the number of possible "
    "combinations since the character set to guess has both letters and numbers. Second because the password will be longer if numbers are add to it. "
    "For example, a password of length 8 that only used lowercase letters will be 26^8 = 208,000,000,000 total possibiliies, now assuming this password "
    "could also contain numbers 0-9 that will bring it the possible combinations to 36^8 = 3,000,000,000,000",
    "Numbers inlucded in passwords are usesd in very predictable patterns. For example, it is often for a user to include 1-3 numbers at the end of their "
    "password or user numbers cooresponding to their birthday. Also, it is very common for patterns like 123, 789, 123321, etc.",
    "Increases tower range",
    "From the Sony and Gawker password breach it was found that about 1/3 of all passwords contain atleast one number.",
    0,
    0,
    25,
    3,
    30,
    ":/File/GameResources/upgradeIcons/numbers.png"
};

const struct Upgrade randomize = {
    "Randomize Password",
    3,
    "Shuffle the password into a new random order",
    "Most password brute force attempts reliely on the fact that the password exists in dictionary of known password. A dictonary of known passwords "
    "is usually a very large list created from past data breaches. If your password's characters are in a random order or at least a seemingly random "
    "order then it will mostly likely not exist in a known password dictionary make it a lot more difficult for a brute force attcker to crack ",
    "If you reuse your 'random' password in multiple places it could still be in a password dictionary if one of the services you used was breached. Also, "
    "even if the characters of your password are in a seemingly random order that won't stop a simple brute force attack if the length is short.",
    "Increases tower damage",
    "From an analysis of Sony and Gawker breached passwords it was observed that 2/3rd's of all passwords had an obvious pattern to them, whether it's a "
    "name, place, word, keyboard pattern, etc only about 1/3 of passwords didn't have an obvious pattern.",
    0,
    10,
    0,
    4,
    30,
    ":/File/GameResources/upgradeIcons/random.png"
};

const struct Upgrade sha1 = {
    "SHA-1 Hash",
    4,
    "Hash the password with the SHA-1 hashing algorithm. This algorithm outputs a psuedorandom 160 bit value, so a string of 40 characters",
    "SHA-1 is a hasing algirthms used to store and verify your password on a server. This way if the servers database is breached an attacker "
    "would only have access to the hashed version of your password not the plaintext value.",
    "SHA-1 is computation very fast which is a downside since it allows an attacker to brute force may possibiliies in a short amount "
    "of time to try and crack your password. Also there are large collections of databases that contain common SHA-1 hashes so if you have a "
    "common password then having it's hash doesn't make it much more secure.",
    "Increases tower range",
    "SHA-1 was first discoved in 2001 and highly optimized processor farms can do billions of SHA-1 hashes in a single second",
    1,
    15,
    0,
    5,
    60,
    ":/File/GameResources/upgradeIcons/function.png"
};

const struct Upgrade md5 = {
    "MD5 Hash",
    5,
    "Hash the password with the MD5 hashing alogorithm. This algorithm outpput a pseudorandom 128 bit value, so a string of 32 characters",
    "MD5 is a hasing algirthms used to store and verify your password on a server. This way if the servers database is breached an attacker "
    "would only have access to the hashed version of your password not the plaintext value.",
    "MD5 is computation very fast which is a downside since it allows an attacker to brute force may possibiliies in a short amount "
    "of time to try and crack your password. Also there are large collections of databases that contain common MD5 hashes so if you have a "
    "common password then having it's hash doesn't make it much more secure.",
    "Increases tower range",
    "MD5 was first discoved in 1991 and highly optimized processor farms can do billions of md5 hashes in a single second",
    1,
    0,
    30,
    6,
    60,
    ":/File/GameResources/upgradeIcons/function.png"
};

const struct Upgrade md5TripleHash = {
    "Triple MD5 Hash",
    6,
    "Hash the password three consecutive times with MD5 hash function. md5(md5(md5(password)))",
    "Hashing a password multiple times provides even more security in the event that a server's database gets breached. An attacker wouldn't only "
    "have to crack the hash but they would have to do it three times. Not only that since since the output of a md5 hash is 32 characters they would "
    "neet to crack these large values. ",
    "MD5 is still an unsecure algorithm since computations are still done very quick and only rehashing two times doesn't add that much more "
    "computational work. ",
    "Increases tower range",
    "More secure hashing algorithms use this iterative idea of rehashing values to increase the amount of compultation work and memory used to create the hash",
    1,
    0,
    90,
    7,
    60,
    ":/File/GameResources/upgradeIcons/function.png"
};

const struct Upgrade sha1TripleHash = {
    "Triple SHA-1 Hash",
    7,
    "Hash the password three consecutive times with SHA-1 hash function. sha-1(sha-1(sha-1(password))))",
    "Hashing a password multiple times provides even more security in the event that a server's database gets breached. An attacker wouldn't only "
    "have to crack the hash but they would have to do it three times. Not only that since since the output of a sha-1 hash is 40 characters they would "
    "neet to crack these large values. ",
    "SHA-1 is still an unsecure algorithm since computations are still done very quick and only rehashing two times doesn't add that much more "
    "computational work. ",
    "Increases tower damage",
    "More secure hashing algorithms use this iterative idea of rehashing values to increase the amount of compultation work and memory used to create the hash",
    1,
    45,
    0,
    8,
    60,
    ":/File/GameResources/upgradeIcons/function.png"
};

const struct Upgrade basicSalt = {
    "Add Salt",
    8,
    "Add a password salt to your hash. Salt is a value the is prepended or appended to your password before it is hashed.",
    "hash(saltValue + password) Adding a salt to your password makes the hashed value a lot more secure. The salt value is stored alongside your password hash. If an attacker compromises a database of " 
    "salted password hashes they have to do a lot more work to reverse enginneer the original password. ",
    "The shorter the salt value is the less additional secureity it provides. Short salt values add little value. Also it is a mistake to reuse a salt which "
    "would ultimately make it useless.",
    "Increases tower damage",
    "Early Unix implementations only salted password with a 12-bit value so there was only 4,096 possible salts.",
    2,
    50,
    0,
    9,
    100,
    ":/File/GameResources/upgradeIcons/salt.png"
};

const struct Upgrade basicPepper = {
    "Add Pepper",
    9,
    "Add a password pepper to your hash. Pepper is a secret value the is prepended or appended to your password before it is hashed.",
    "hash(pepper + passowrd) Adding a pepper to your hash makes the value a lot more secure and harder to crack. Unlike a salt value the pepper is not stored "
    "along side the hash instead it is stored somewhere in hardward. ",
    "Sometimes a pepper value is shared amoung all hashes, in that case if one of the hashes are cracked this severaly decreases the security of the rest "
    "of the value. For this reason it is common to have a pepper unique for each user. ",
    "Increases tower range",
    "The term 'Pepper' came from colloquial use it is also commonly referend to as a 'secret salt' or 'local salt'.",
    2,
    0,
    100,
    10,
    100,
    ":/File/GameResources/upgradeIcons/pepper.png"
};


const struct Upgrade bcryptHash = {
    "Add bcrypt Hash",
    10,
    "Hash password with BCrypt passowrd-hashing function. This function used a time and memory expensive computation of many iterations.",
    "Bcrypt is a highly secure password hashing function that is commonly used today. The security of Bcrypt comes from the amount of cpu time and memeory it takes "
    "to do a single hash. This is important because it protects against brute force attacks. ",
    "A downside of BCyrpt is that it can be complicated to implement and take can take up alot of memeory resources.",
    "Increases tower damage and range",
    "BCyrpt was originally specified in 1999 and the modern implementations have been implemented around 2014 to imporove security and patch bugs. ",
    3,
    60,
    100,
    11,
    150,
    ":/File/GameResources/upgradeIcons/function.png"
};

const struct Upgrade argon2idHash = {
    "Add Argon2id Hash", 
    11,
    "Hash the password with Argon2id passowrd hashing function",
    "Argon2id is a modern secure way of creating secure password hashes. Primarly because it takes a lot of computational work (ie. time and memory resources) to "
    "compute the hash. This feature of slow computing defends against brute force attacks. ",
    "A downside of Argon2id is that it can be hard to implement since it's such a new algorithm and can also take can take up alot of memeory resources.",
    "Increases tower damage and range",
    "Argon2id was winner of the 2015 Password Hashing Competition",
    3,
    60,
    110,
    12,
    150,
    ":/File/GameResources/upgradeIcons/function.png"
};

const map<int, QString> PASSWORD_STRENGTH_DESC {
    {0, "You've selected a password in the top most 100 commonly used passwords. Brute force attackers will use a dictionary of passwords "
        "that will definately contain this obvious password, leading it to be cracked in under a second. The password contains very common words, "
        "numbers, or keyboard patterns that many people use. The short length and lack of symbols or special characters makes this password very "
        "suseptable to brute force attacks. This is very unsecure password!"},
    {1, "You've selected a password in the top most 10,000 commonly used passwords. Brute force attackers will use a dictionary of passwords "
        "that will most likey contain this password, leading it to be cracked in a few seconds. The password contains very common words, "
        "numbers, or keyboard patterns that many people use. The short length and lack of symbols/special characters makes this password very "
        "susceptible to brute force attacks. This is an unsecure password!"},
    {2, "You've selected a decently secure password that may contain lower/uppcase letter, numbers, and symbols such as $, !, or &. The characters "
        "apear to be in random order with no obvious patterns so it will mostly likey not exist in a password dictionary. Therefore an attacker would "
        "have to brute force all possible combinations of letters, numbers, and three symbols to crack this password which may or may not be "
        "computational infeastable to do so. This password could be made more secure by increasing it's length and using a larger set of symbols."},
    {3, "You've selected a very secure password. It is a longer length and contains upper/lower case letters, numbers, symbols and special characters "
        "like } ; ( ) - : } \\ * ! ; . ^ + [ ] $ ? % | ` > < / @ # _ ~. This password is crytogrphaically secure meaning to brute force it would require "
        "at least hundreds of thousands of years of computation work even on the most optimized processors. The length could be increased to make "
        "it more secure against brute force but practically if this password is being compomised it won't be from a brute force attack."}
};

const map<int, vector<QString>> PASSWORDS_COLLECTION {
    // 0: TOP 100 most commonly used password, cracked instantly and
    {0,
        {"password", "123456", "qwerty", "111111", "abc123", "princess", "iloveyou",
         "qwerty123", "asdfghjk", "dragon", "football", "killer", "pokemon", "asdf1234",
         "superman", "sunshine", "admin", "password123", "9999999", "admin"}
    },
    // 1: contained within most password lists but if brute forced may take a little while
    {1,
        {"gfhjkmg", "23051987", "z1x2c3v4", "lucky13", "summer69", "q1w2e3r4",
         "nokia6233", "123qwe123", "gordon24", "front242", "Turkey50", "chicago1",
         "*****", "1qaz1qaz", "31415926"}
    },
    // decently secure passwords which will take a while to brute force since they're random gen with numbers, specials ($, &, !)
    {2,
        {"R&tBu9G", "ynA2m&D", "hx3T0Y$", "OFE&aG16x", "V$0NQ4brV", "vz$85eRDw", "Hc2$CL!Sy",
        "uu3&OFd33", "dWTu6$bh", "ceY91H$J", "l628B5&G", "H9WmTY&J", "gqB7!7s1", "HPm!2ytx", "o$X6cbMf"}
    },
    // very strong passwords, long containing many special characters
    {3,
        {"h}vxWX;iy7gfY(-:SYI}k)N^", "U&;u6g}/Wx$|TCcJgW?0;Te/", "L:4;MC||>9H*mzz/k)xsG;oZ", "p*!$j;n;0RY#zgY4i8JuuOe}",
        "bqN-;5FL3CLKb%|<w>Z*d`79", "sOa68juT&:+h!~2lObh=dKwU", "m+6o1jPgn,U^e}5^PXW8x}:_", "nvHA;gQi0n+:AY.F_+Y8V4M&",
        "Z$[]QyGtf+)r;UTF8B;-C]IV", "n.[))`4o]NleC{U@Y0Xh?e15"}
    },
};

enum PasswordType { Master, Tower };



const map<int, QString> ROUND_DESCRIPTIONS = {
    {0, "Computer is now launching. Please wait warmly."},
    {1, "Hello! Welcome to the Password Tower Defense! I'm here to help you as you progress along the game! To start, try placing down a standard basic tower and clicking Start."},
    {2, "As you're able to see, these towers are able to fight back against hackers. Each"
     " one also comes with its own password that determines its starting strength! Watch out for keyloggers next round."
     " When they are killed, they will pick a random tower and leak its password! And a leaked password, no matter how good, is essentially"
     " worthless, meaning they will lose their ability to help you. Be sure to repair any tower that gets its password leaked to get it up"
     " and ready to defend again!"},
    {3, "As you collect more points, you can place towers of different types to help you survive the onslaught of attackers. Bounce Towers shoot"
     " bullets that bounce around the screen, while freeze towers freeze the towers closest to them! These have the added bonus of"
     " nullifying any attacker effects that they perform when killed."},
    {4, "Good job surviving the adware. Click the wrong button, and they will likely find some security risk on your computer, causing."
     "a bit of damage. Be warned, however, as the"
     " next round contains the dreaded Meltdown. Meltdown is a vulnerability that exists on the hardware level. This computer is not designed"
     " to protect against it, meaning if you are hit by it, it's game over immediately. Better prepare yourself for this."},
    {5, "You made it past Meltdown! Good job! Now comes the hard part. Towers will begin spawning randomly, so watch out!"},
    {6, "Three random waves incoming! Be careful!"},
    {7, "A full onslaught of 35 enemies making its way. Prepare yourself."},
    {8, "Boss wave is here! This one has two instances of Meltdown."},
    {9, "These are some uneven waves I'm seeing."},
    {10, "Sometimes, you just gotta deal with the entire hoard of enemies."},
    {11, "I suppose that isn't too many extra guys."},
    {12, "5 whole Meltdowns. Call that a Breakdown."},
    {13, "Some small relief at first before everything falls apart from chaos."},
    {14, "Can you deal with 70 enemies all coming for you without pause?"},
    {15, "It's time for the final boss. Hopefully, you got yourself some extremely high security for what you're about to see. I wish"
     " you luck, and am proud to say I was able to get this far with you."},
    {16, "You have beaten the final challenge! You truly are a security master! Take this final password. You've earned it!"
     " Now go! Use it and create the most secure account password you can!"}
};

#endif // GLOBALS_H
