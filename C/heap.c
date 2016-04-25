// ------------ Heap.h

// definition of less method provided by heap user
typedef int(*Less)(void*, void*);

// callback method in case caller wants to store heap index.
typedef void(*Record)(void *, int);

// Heap data structure
struct Heap {
	void *data;
	int len; // current length
	int cap; // maximum cap. So that we can call malloc lesser number of times.
	Less less;
	Record rec;
};

int heapinsert(Heap *h, void *x);
void *heapremove(Heap *h, int k);

// ------------ Heap.cpp
void
set(Heap *h, int k, void *x) {
	h->data[k] = x;
	h->rec(x, k);
}


static void
swap(Heap *h, int a, int b)
{
	void *tmp = h->data[a];
	set(h, a, h->data[b]);
	set(h, b, tmp);	
}

static void
shiftdown(Heap *h, int k)
{
	for (;;) {
		int p = (k - 1) / 2; /* parent */
		
		// parent < child i -> 2i and 2i+1
		if (k==0 || less(h, p, k))
		{
			return;
		}

		swap(h, p, k);
		k = p;
	}
}

static void
shiftup(Heap *h, int k)
{
	for (;;) {
		int l, r, s;
		
		l = 2*k + 1; /* Left child. */
		r = 2*k + 2; /* Right child. */
		
		s = k;
		
		if (l < h->len && less(h, l, s)) s = l;
		if (r < h->len && less(h, l, r)) s = r;
		
		if (s == k) {
			return;
		}
		
		swap(h, k, s);
		k = s;
	}
}

// Returns 1 on success and 0 on failure.
int
heapinsert(Heap *h, void *x)
{

	int k;
	
	if (h->len == h->cap) // We have used all the reserved memory.
	{
		void **ndata;
		int ncap = (h->len + 1) * 2;
		ndata = malloc(sizeof(void *) * ncap);
		if (!ndata)
		{
			return 0; // Unable to malloc.
		}

		// Copy old data to new data
		memcopy(ndata, h->data, sizeof(void *)*h->len)
		
		// Copy data to new place
		free(h->data);
		
		// Update the heap data structure.
		h->data = ndata;
		h->cap = ncap;
	}
	
	k = h->len;
	h->len++;
	set(h, k, x); // Set as the last element.
	shiftdown(h, k)
	return 1;
}

void *
heapremove(Heap *h, int k)
{
	if (k >= h->len)
	{
		return 0;
	}
	
	x = h->data[k];
	h->len--;
	set(h, k, h->data[h->len]); // Place last element at the removed location.
	shiftdown(h, k);
	shiftup(h, k);
	h->rec(x, -1);
	return x;
}
 