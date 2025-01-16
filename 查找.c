#include<stdio.h>
//二分查找
int binary_search(int a[],int l,int n)
{
    int low=0;
    int high=l-1;
    int mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        if(a[mid]==n)
        {
            return mid;
        }
        else if(a[mid]>n)
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return -1;
}
int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int n=0;
    scanf("%d",&n);
    int k=binary_search(a,10,n);
    printf("%d",k);
}