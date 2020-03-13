#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10, /* TODO: fill in "n" i.e. instance sizes */ };

void fill_increasing(int *t, unsigned int n) {
    int i;
    for (i=0;i<n;i++){
        t[i]=i;

    }
}

void fill_decreasing(int *t, unsigned int n) {
   int w[n];
   int i;
   w[n]=n;
   for (i=0;i<n;i++)
   {
    n--;
    w[n]=n;
   }
}

void fill_vshape(int *t, unsigned int n) {
    int i;
     for(i=0;i<n;i++){
    t[i]=i++;
  }
    int start=t[n-1];
    int end=t[n-2];
    t[0]=start;
    t[n-1]=end;

}

void selection_sort(int *t, unsigned int n) {
    	int pos, podmiana;
	for (int c=0;c<(n);c++)
        for (int c=0;c<(n--);c++){
			pos=c;
			for (int d=c++;d<n;d++){
				if (t[pos]>t[d])
					pos=d;
					}
			if (pos!=c){
				podmiana=t[c];
				t[c]=t[pos];
				t[pos]=podmiana;
			}
		}

}

void insertion_sort(int *t, unsigned int n) {
	int d, c;

	for (int j=1;j<n-1;j++)
	{
		d=j;
	}
	while (d>0&&t[d]<t[d-1])
	{
		c=t[d];
		t[d]=t[d-1];
		t[d-1]=c;
		d--;
	}
}

void swap (int* a, int* b){
    int t=*a;
    *a=*b;
    *b=t;
}

int part (int *t, unsigned int n,int g[], int low, int high){
    int pivot=g[high];
    int i=(low-1);
    int j;
    for (j=low;j<=high-1;j++)
    {
        if(g[j]<pivot)
        {
            i++;
            swap(&g[i],&g[j]);
        }
    }
    swap(&g[i+1],&g[j]);
    return (i+1);
    }
void quick_sort(int *t, unsigned int n,int g[], int low, int high) {
    if (low<high)
    {
        int pi=part(g,low,high);
        quick_sort(g,low,pi-1);
        quick_sort(g,pi+1,high);
    }

}

void heap(int*t, unsigned int n, int i){
    int max=i;
    int left=2*i+1;
    int right=2*i+2;
        if (left<n&&t[left]>t[max])
            max=left;
        if (right<n&&t[right]>t[max])
            max=right;
        if (max!=i){
            swap(&t[i], &t[max]);
            heap(t,n,max);
        }
}
void heap_sort(int *t, unsigned int n) {
    for (int i=n/2-1;i>=0;i--)
        heap(t,n,i);
    for (int i=n-1;i>=0;i--){
        swap(&t[0],&t[i]);
        heap(t,i,0);
    }
}


void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
