# OS_T1_V19_Familiya — macOS uchun

Ushbu loyiha 1-topshiriqning 19-varianti uchun:
- A qism: `Hello World` kompilyatsiyasining bosqichlari;
- 1-masala: Sezar shifri;
- 2-masala: ikkilik qidiruv daraxti (BST).

> Topshiriq varag'ida Linux/WSL2 va GCC ko'rsatilgan. macOS'da odatda Apple Clang mavjud. O'qituvchi aynan GCC talab qilsa, Linux/VM yoki boshqa tasdiqlangan muhitdan foydalaning.

## 1. Xcode Command Line Tools

Terminalda tekshiring:

```sh
clang --version
```

Agar topilmasa:

```sh
xcode-select --install
```

## 2. A qismi: Hello World — 4 bosqich

Loyiha papkasida buyruqlarni birma-bir bajaring:

```sh
clang -E hello.c -o hello.i
clang -S hello.i -o hello.s
clang -c hello.s -o hello.o
clang hello.o -o hello
./hello
```

Kutiladigan natija:

```text
Hello World
```

Fayllar ma'nosi:
- `hello.i` — preprocessor'dan o'tgan C kodi;
- `hello.s` — assembly kodi;
- `hello.o` — obyekt fayli, hali yakuniy bajariluvchi dastur emas;
- `hello` — linker yaratgan bajariluvchi fayl.

Fayl hajmlarini ko'rish:

```sh
ls -lh hello.c hello.i hello.s hello.o hello
```

## 3. 1-masala: Sezar shifri

```sh
clang -std=c11 -Wall -Wextra -pedantic main_task1.c -o task1
./task1
```

Dastur matn va butun sonli kalit so'raydi. Deshifrlashda kalitning teskari yo'nalishi ishlatiladi. Faqat ingliz alifbosidagi A-Z/a-z harflar siljiydi; bo'sh joy, raqam va tinish belgilari saqlanadi.

### Sinovlar

1. Shifrlash: tanlov `1`, matn `Hello, World!`, kalit `3` → `Khoor, Zruog!`
2. Deshifrlash: tanlov `2`, matn `Khoor, Zruog!`, kalit `3` → `Hello, World!`
3. Shifrlash: tanlov `1`, matn `Abc XYZ!`, kalit `-1` → `Zab WXY!`
4. Xato kiritish: tanlov `7` → xato xabari chiqadi.

## 4. 2-masala: BST

```sh
clang -std=c11 -Wall -Wextra -pedantic main_task2.c -o task2
./task2
```

### Sinovlar

1. Miqdor `5`; sonlar `8 3 10 1 6`; qidiruv `6` → in-order `1 3 6 8 10`, son topiladi.
2. Miqdor `3`; sonlar `4 2 7`; qidiruv `5` → in-order `2 4 7`, son topilmaydi.
3. Miqdor `0`; qidiruv `5` → daraxt bo'sh, son topilmaydi.
4. Xato kiritish: miqdor o'rniga `abc` → xato xabari chiqadi.

Har bir testni Terminalda o'zingiz bajaring va natija ko'rinadigan skrinshotlarni hisobotga qo'shing. Testlar soni kamida 3 ta bo'lsin; kamida bittasi xato kiritishni tekshirishi kerak.

## 5. GitHub

Repozitoriy nomi topshiriq varag'idagi formatga mos bo'lsin: `OS_T1_V19_Familiya`.

Quyidagilarni joylang:
- `hello.c`, `hello.i`, `hello.s`, `hello.o`, `hello` (yoki macOS'da hosil bo'lgan bajariluvchi fayl);
- `main_task1.c`;
- `main_task2.c`;
- `README.md`;
- hisobot PDF'i.

GitHub repozitoriyasini `public` qiling. F.I.Sh., guruh, fan nomi va o'qituvchi talab qilgan boshqa ma'lumotlarni o'zingiz to'ldiring.
