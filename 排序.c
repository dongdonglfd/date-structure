#include<stdio.h>
//插入排序
void insertsort(int a[],int n)
{
    int i,j,temp;
    for(i=1;i<n;i++)
    {
        if(a[i]<a[i-1])
        {
            temp=a[i];
            for(j=i-1;j>=0&&a[j]>temp;--j)
            {
                a[j+1]=a[j];
            }
            a[j+1]=temp;
        }
    }
}
//希尔排序
void shellsort(int a[],int n)
{
    int d,i,j,k;
    for(d=n/2;d>=1;d=d/2)
    {
        for(i=d;i<n;++i)
        {
            if(a[i]<a[i-d])
            {
                k=a[i];
                for(j=i-d;j>0&&k<a[j];j-=d)
                {
                    a[j+d]=a[j];
                }
                a[j+d]=k;
            }
        }
    }
}
//冒泡排序
void bubblesort(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
}
//快速排序
int partition(int a[],int low,int high);
void quicksort(int a[],int low,int high)
{
    if(low<high)
    {
        int p=partition(a,low,high);
        quicksort(a,low,p-1);//左子表
        quicksort(a,p+1,high);//右字表
    }
}
//用第一个元素将带排序序列划分为左右两个部分
int partition(int a[],int low,int high)
{
    int p=a[low];
    while(low<high)
    {
        while(low<high&&a[high]>=p)
        {
            --high;
        }
        a[low]=a[high];
        while(low<high&&a[low]<=p)
        {
            ++low;
        }
        a[high]=a[low];
    }
    a[low]=p;
    return low;
}
//选择排序
void selectsort(int a[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        int min=i;
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[min])
                min=j;
        }
        if(min!=i)
        {
            int t=a[i];
            a[i]=a[min];
            a[min]=t;
        }
    }
}
int main()
{
    int a[10]={1,5,6,3,7,8,4,10,11,12};
    selectsort(a,10);
    for(int i=0;i<10;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}