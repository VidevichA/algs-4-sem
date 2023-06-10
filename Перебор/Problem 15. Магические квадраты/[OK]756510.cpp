#include <iostream>
#include <vector>
#include <fstream>

struct Domino
{
    int a, b;
    bool used;
    Domino(int a_, int b_, bool used_) : a(a_), b(b_), used(used_) {}
};

std::ifstream fin;
std::ofstream fout;

std::vector<bool> used(8, false);
std::vector<bool> used_rev(8, false);
std::vector<Domino> dominoes;

void MakeDomino()
{
    dominoes.emplace_back(0, 0, false);
    dominoes.emplace_back(1, 1, false);
    dominoes.emplace_back(2, 2, false);
    dominoes.emplace_back(3, 3, false);
    dominoes.emplace_back(4, 4, false);
    dominoes.emplace_back(5, 5, false);
    dominoes.emplace_back(6, 6, false);
    dominoes.emplace_back(0, 1, false);
    dominoes.emplace_back(1, 0, false);
    dominoes.emplace_back(0, 2, false);
    dominoes.emplace_back(2, 0, false);
    dominoes.emplace_back(0, 3, false);
    dominoes.emplace_back(3, 0, false);
    dominoes.emplace_back(0, 4, false);
    dominoes.emplace_back(4, 0, false);
    dominoes.emplace_back(0, 5, false);
    dominoes.emplace_back(5, 0, false);
    dominoes.emplace_back(0, 6, false);
    dominoes.emplace_back(6, 0, false);
    dominoes.emplace_back(1, 2, false);
    dominoes.emplace_back(2, 1, false);
    dominoes.emplace_back(1, 3, false);
    dominoes.emplace_back(3, 1, false);
    dominoes.emplace_back(1, 4, false);
    dominoes.emplace_back(4, 1, false);
    dominoes.emplace_back(1, 5, false);
    dominoes.emplace_back(5, 1, false);
    dominoes.emplace_back(1, 6, false);
    dominoes.emplace_back(6, 1, false);
    dominoes.emplace_back(2, 3, false);
    dominoes.emplace_back(3, 2, false);
    dominoes.emplace_back(2, 4, false);
    dominoes.emplace_back(4, 2, false);
    dominoes.emplace_back(2, 5, false);
    dominoes.emplace_back(5, 2, false);
    dominoes.emplace_back(2, 6, false);
    dominoes.emplace_back(6, 2, false);
    dominoes.emplace_back(3, 4, false);
    dominoes.emplace_back(4, 3, false);
    dominoes.emplace_back(3, 5, false);
    dominoes.emplace_back(5, 3, false);
    dominoes.emplace_back(3, 6, false);
    dominoes.emplace_back(6, 3, false);
    dominoes.emplace_back(4, 5, false);
    dominoes.emplace_back(5, 4, false);
    dominoes.emplace_back(4, 6, false);
    dominoes.emplace_back(6, 4, false);
    dominoes.emplace_back(5, 6, false);
    dominoes.emplace_back(6, 5, false);
}

int MakeSquares()
{
    int current = 0, counter = 0;
    for (int i1 = 0; i1 < dominoes.size(); i1++)
    {
        if (i1 < 7)
        {
            dominoes[i1].used = true;
        }
        else
        {
            used[1] = true;
            if (i1 % 2 == 1)
            {
                used_rev[1] = true;
                dominoes[i1].used = true;
                dominoes[i1 + 1].used = true;
            }
            else
            {
                used_rev[1] = false;
                dominoes[i1].used = true;
                dominoes[i1 - 1].used = true;
            }
        }

        for (int i2 = 0; i2 < dominoes.size(); i2++)
        {
            if (dominoes[i2].used)
            {
                continue;
            }
            current = dominoes[i1].a + dominoes[i1].b + dominoes[i2].a + dominoes[i2].b;

            if (i2 < 7)
            {
                dominoes[i2].used = true;
            }
            else
            {
                used[2] = true;
                if (i2 % 2 == 1)
                {
                    used_rev[2] = true;
                    dominoes[i2].used = true;
                    dominoes[i2 + 1].used = true;
                }
                else
                {
                    used_rev[2] = false;
                    dominoes[i2].used = true;
                    dominoes[i2 - 1].used = true;
                }
            }

            for (int i3 = 0; i3 < dominoes.size(); i3++)
            {
                if (dominoes[i3].used || dominoes[i1].a + dominoes[i3].b > current ||
                    dominoes[i1].a + dominoes[i3].a > current || dominoes[i1].b + dominoes[i3].b > current)
                {
                    continue;
                }
                if (i3 < 7)
                {
                    dominoes[i3].used = true;
                }
                else
                {
                    used[3] = true;
                    if (i3 % 2 == 1)
                    {
                        used_rev[3] = true;
                        dominoes[i3].used = true;
                        dominoes[i3 + 1].used = true;
                    }
                    else
                    {
                        used_rev[3] = false;
                        dominoes[i3].used = true;
                        dominoes[i3 - 1].used = true;
                    }
                }

                for (int i4 = 0; i4 < dominoes.size(); i4++)
                {
                    if (dominoes[i4].used)
                    {
                        continue;
                    }

                    if (dominoes[i1].a + dominoes[i3].a + dominoes[i4].a > current ||
                        dominoes[i2].b + dominoes[i4].b > current ||
                        dominoes[i1].b + dominoes[i3].b + dominoes[i4].b > current)
                    {
                        continue;
                    }
                    if (i4 < 7)
                    {
                        dominoes[i4].used = true;
                    }
                    else
                    {
                        used[4] = true;
                        if (i4 % 2 == 1)
                        {
                            used_rev[4] = true;
                            dominoes[i4].used = true;
                            dominoes[i4 + 1].used = true;
                        }
                        else
                        {
                            used_rev[4] = false;
                            dominoes[i4].used = true;
                            dominoes[i4 - 1].used = true;
                        }
                    }

                    for (int i5 = 0; i5 < dominoes.size(); i5++)
                    {
                        if (dominoes[i5].used)
                        {
                            continue;
                        }

                        if (dominoes[i1].a + dominoes[i3].a + dominoes[i4].a + dominoes[i5].a != current ||
                            dominoes[i1].b + dominoes[i3].b + dominoes[i4].b + dominoes[i5].b != current ||
                            dominoes[i2].b + dominoes[i5].a + dominoes[i4].b > current)
                        {
                            continue;
                        }

                        if (i5 < 7)
                        {
                            dominoes[i5].used = true;
                        }
                        else
                        {
                            used[5] = true;
                            if (i5 % 2 == 1)
                            {
                                used_rev[5] = true;
                                dominoes[i5].used = true;
                                dominoes[i5 + 1].used = true;
                            }
                            else
                            {
                                used_rev[5] = false;
                                dominoes[i5].used = true;
                                dominoes[i5 - 1].used = true;
                            }
                        }

                        for (int i6 = 0; i6 < dominoes.size(); i6++)
                        {
                            if (dominoes[i6].used)
                            {
                                continue;
                            }

                            if (dominoes[i3].a + dominoes[i3].b + dominoes[i6].a + dominoes[i6].b != current ||
                                dominoes[i2].b + dominoes[i6].a + dominoes[i5].a + dominoes[i4].b != current ||
                                dominoes[i2].b + dominoes[i6].b > current ||
                                dominoes[i2].a + dominoes[i6].a > current)
                            {
                                continue;
                            }
                            if (i6 < 7)
                            {
                                dominoes[i6].used = true;
                            }
                            else
                            {
                                used[6] = true;
                                if (i6 % 2 == 1)
                                {
                                    used_rev[6] = true;
                                    dominoes[i6].used = true;
                                    dominoes[i6 + 1].used = true;
                                }
                                else
                                {
                                    used_rev[6] = false;
                                    dominoes[i6].used = true;
                                    dominoes[i6 - 1].used = true;
                                }
                            }

                            for (int i7 = 0; i7 < dominoes.size(); i7++)
                            {
                                if (dominoes[i7].used)
                                {
                                    continue;
                                }

                                if (dominoes[i1].a + dominoes[i3].b + dominoes[i7].a > current ||
                                    dominoes[i2].b + dominoes[i6].b + dominoes[i7].b > current ||
                                    dominoes[i2].a + dominoes[i6].a + dominoes[i7].a > current ||
                                    dominoes[i4].a + dominoes[i4].b + dominoes[i7].a + dominoes[i7].b != current)
                                {
                                    continue;
                                }

                                if (i7 < 7)
                                {
                                    dominoes[i7].used = true;
                                }
                                else
                                {
                                    used[7] = true;
                                    if (i7 % 2 == 1)
                                    {
                                        used_rev[7] = true;
                                        dominoes[i7].used = true;
                                        dominoes[i7 + 1].used = true;
                                    }
                                    else
                                    {
                                        used_rev[7] = false;
                                        dominoes[i7].used = true;
                                        dominoes[i7 - 1].used = true;
                                    }
                                }

                                for (int i8 = 0; i8 < dominoes.size(); i8++)
                                {
                                    if (dominoes[i8].used)
                                        continue;
                                    if (dominoes[i5].a + dominoes[i5].b + dominoes[i8].a + dominoes[i8].b != current ||
                                        dominoes[i2].b + dominoes[i6].b + dominoes[i7].b + dominoes[i8].b != current ||
                                        dominoes[i2].a + dominoes[i7].a + dominoes[i6].a + dominoes[i8].a != current ||
                                        dominoes[i3].b + dominoes[i1].a + dominoes[i8].b + dominoes[i7].a != current)
                                    {
                                        continue;
                                    }

                                    fout << "--------\n";
                                    fout << dominoes[i1].a << " " << dominoes[i1].b << " " << dominoes[i2].a << " " << dominoes[i2].b << "\n";
                                    fout << dominoes[i3].a << " " << dominoes[i3].b << " " << dominoes[i6].a << " " << dominoes[i6].b << "\n";
                                    fout << dominoes[i4].a << " " << dominoes[i4].b << " " << dominoes[i7].a << " " << dominoes[i7].b << "\n";
                                    fout << dominoes[i5].a << " " << dominoes[i5].b << " " << dominoes[i8].a << " " << dominoes[i8].b << "\n";
                                    counter++;
                                }
                                dominoes[i7].used = false;
                                if (used[7])
                                {
                                    if (!used_rev[7])
                                    {
                                        dominoes[i7 - 1].used = false;
                                    }
                                    else
                                    {
                                        dominoes[i7 + 1].used = false;
                                    }
                                }
                                used[7] = false;
                            }
                            dominoes[i6].used = false;
                            if (used[6])
                            {
                                if (!used_rev[6])
                                {
                                    dominoes[i6 - 1].used = false;
                                }
                                else
                                {
                                    dominoes[i6 + 1].used = false;
                                }
                            }
                            used[6] = false;
                        }
                        dominoes[i5].used = false;
                        if (used[5])
                        {
                            if (!used_rev[5])
                            {
                                dominoes[i5 - 1].used = false;
                            }
                            else
                            {
                                dominoes[i5 + 1].used = false;
                            }
                        }
                        used[5] = false;
                    }
                    dominoes[i4].used = false;
                    if (used[4])
                    {
                        if (!used_rev[4])
                        {
                            dominoes[i4 - 1].used = false;
                        }
                        else
                        {
                            dominoes[i4 + 1].used = false;
                        }
                    }
                    used[4] = false;
                }
                dominoes[i3].used = false;
                if (used[3])
                {
                    if (!used_rev[3])
                    {
                        dominoes[i3 - 1].used = false;
                    }
                    else
                    {
                        dominoes[i3 + 1].used = false;
                    }
                }
                used[3] = false;
            }
            dominoes[i2].used = false;
            if (used[2])
            {
                if (!used_rev[2])
                {
                    dominoes[i2 - 1].used = false;
                }
                else
                {
                    dominoes[i2 + 1].used = false;
                }
            }
            used[2] = false;
        }
        dominoes[i1].used = false;
        if (used[1])
        {
            if (!used_rev[1])
            {
                dominoes[i1 - 1].used = false;
            }
            else
            {
                dominoes[i1 + 1].used = false;
            }
        }
        used[1] = false;
    }
    return counter;
}

int main()
{
    fin.open("input.txt");
    int n;
    fin >> n;
    fin.close();
    fout.open("output.txt");
    MakeDomino();

    int counter = MakeSquares();
    fout << "Count=" << counter;
    fout.close();
    return 0;
}