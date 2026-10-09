
# CSV Translator

> Note: The CSV file is UTF-8 encoded. Arabic text may appear incorrectly in the terminal depending on the font and encoding settings.

## Commands

```bash
cd CSVTranslate
g++ -std=c++17 main.cpp
./a.exe data.csv
```

## Program usage

- `getlang` -> print the current language
- `setlang [LANGUAGE]` -> set language (Example: `setlang German`)
Available are: English, German, Spanish, Arabic, Dog

## Translation behavior

Typing any recognized keyword returns a translation.

- Example: `hello` → German: `hallo`


//Info: file STYLED by AI