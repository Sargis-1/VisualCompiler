int foo();
int main()
{
    foo();
}

int foo()
{
    int fi = 10;
    while (fi) {
        fi -= 1;
        if (fi == 8) {
            break;
        }
        continue;
    }

    if (int ifi = 5) {
        short ifsh = 2;
        while (ifsh < ifi) {
            ifsh += 1;
            if (ifsh == 3) {
                continue;
            } else {
                break;
            }
        }
    }


}


