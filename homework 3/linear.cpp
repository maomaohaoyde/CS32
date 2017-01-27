
bool anyTrue(const double a[], int n)
{   if (n<=0)
    return false;
    
    return somePredicate(a[0])|| anyTrue(a+1, n-1);  // This is not always correct.
}

int countTrue(const double a[], int n)
{   if (n<=0)
{
    return 0;
}
    return somePredicate(a[0])+countTrue(a+1, n-1);  // This is incorrect.
}

int firstTrue(const double a[], int n)
{   if (n<=0)
    return -1;
    if (somePredicate(a[0])) {
        return 0;
    }
    else if (firstTrue(a+1,n-1)==-1)
        
        return -1;
    else
        return 1+firstTrue(a+1, n-1);
   
}

int indexOfMin(const double a[], int n)
{
    if (n<=0)
        return -1;
    if (n==1)
        return 0;
    if (a[0]<=a[indexOfMin(a+1, n-1)+1])
        return 0;
    else
        return indexOfMin(a+1, n-1)+1;
}


bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2<=0) {
        return true;
    }
    if (n1<=0) {
        return false;
    }
    if (a1[0]==a2[0])
        return includes(a1+1,n1-1 , a2+1, n2-1);
    else
        return includes(a1+1, n1-1, a2, n2);
}
