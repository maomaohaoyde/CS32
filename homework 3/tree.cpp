int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2<=0)
        return 1;
    
    if (n1<=0)
        return 0;
    
    if (a1[0]==a2[0])
        return countIncludes(a1+1, n1-1, a2, n2)+countIncludes(a1+1,n1-1 , a2+1, n2-1);
    else
        return countIncludes(a1+1, n1-1, a2, n2);
    
}

void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}


void separate(double a[], int n, double separator,
              int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}


void order(double a[], int n)
{
    if (n<=1)
        return;
    int b,c;
    separate(a, n, a[n/2], b, c);
    order(a, b);
    order(a+c, n-c);
    
}