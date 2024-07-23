int priority(char symbol) 
{
    if (symbol == '+' || symbol == '-') return 1;
    else if (symbol == '*' || symbol == '/') return 2;
    else return 0;
}
