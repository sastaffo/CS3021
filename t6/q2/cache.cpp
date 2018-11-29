#include <cmath>
#include <cstring>
#include <stdio.h>

class Cache
{
    public:
    int addr[32] = {0x0000, 0x0004, 0x000c, 0x2200, 0x00d0, 0x00e0, 0x1130, 0x0028,
                  0x113c, 0x2204, 0x0010, 0x0020, 0x0004, 0x0040, 0x2208, 0x0008,
                  0x00a0, 0x0004, 0x1104, 0x0028, 0x000c, 0x0084, 0x000c, 0x3390,
                  0x00b0, 0x1100, 0x0028, 0x0064, 0x0070, 0x00d0, 0x0008, 0x3394};
    bool hits[32];
    int cache[8][8];
    int cachetmp[8];
    int L; // bytes per line = 4 words per line
    int K; // K-way cache
    int N;
    int tot; // 128 byte total = 32 word total
    int setbits;
    int setmask;
    int tagshift;
    int taglen;
    int H;
    int M;

    Cache(int l, int k)
    {
        L=l;
        K=k;
        tot = 128;
        N = tot / (L*K);
        printf("L=%d,K=%d,N=%d\n", L,K,N);
        setbits = (int)log2(N);
        setmask = N-1;
        tagshift = 4+setbits;
        taglen = 16-tagshift;
        // printf("setbits=%d,setmask=%d,tagshift=%d,taglen=%d\n", setbits, setmask, tagshift, taglen);
        memset(hits, false, 32);
        memset(cachetmp, -1, 8);
        for (int i=0; i<8;i++) memset(cache[i], -1, 32);
        H=0;
        M=0;
    }
    int makenewest(int set, int i)
    {
        cachetmp[0] = cache[set][i];
        //printf("\n  cache   :  ");
        //for (int j=0; j<K; j++) printf("%d ", cache[set][j]);
        //printf("\n  cachetmp:  ");
        for (int j=0;j<i;j++)
            cachetmp[j+1]=cache[set][j];
        //for (int j=0; j<8; j++) printf("%d ", cachetmp[j]);
        //printf("\n  newcache:  ");
        for (int j=0;j<=i;j++)
            cache[set][j]=cachetmp[j];
        //for (int j=0; j<K; j++) printf("%d ", cache[set][j]);
        memset(cachetmp, -1, 32);
        //printf("\n");
    }
    void cachetest()
    {
        int a, tmp, set, tag;
        for(int i=0; i<32;i++)
        {
            a = addr[i];
            //printf("     cache[%d]: ", set);
            //for(int j=0;j<K;j++) printf("%x  ", cache[set][j]);
            //printf("\n");
            tmp = (a>>4);
            set = tmp & setmask; // bitwise and = &
            //printf("\na>>4=%x -> masked=%x\n", tmp,set);
            tag = (a>>tagshift);
            //printf("%04x:",a);
            //printf("set=%d, tag=%d   ",set,tag );
            for (int j=0; j<K;j++) {
                if (tag==cache[set][j]) {
                    hits[i]=true;
                    makenewest(set,j);
                    H++;
                    //printf("= HIT  %d", H);
                    continue;
                }
            }
            if (!hits[i]) {
                cache[set][N-1] = tag; // replace oldest with new entry
                makenewest(set, (N-1));
                M++;
                //printf("= MISS %d", M);
            }
        }
    }
};

int main ()
{
    int l = 16;
    int k = 8;
    Cache c(l, k);
    c.cachetest();
    printf("hits=%d, misses=%d\n", c.H, c.M);
    return(0);
}

/*
// expected hits for for K=2, N=4
bool exphits[] = {false, true,  true,  false, false, false, false, false,
                  true,  true,  false, true,  true,  false, false, false,
                  false, true,  false, true,  true,  false, true,  false,
                  false, false, true,  false, false, false, true,  true};
// checks if correct
for (int j=0; j<32;j++) {
  if (exphits[j] != hits[j]) {
      printf("%2d:%x exp:%s, got:%s\n", j, addr[j],
                exphits[j]?"true":"false", hits[j]?"true":"false");
  }
  else printf("%2d: pass %s\n", j, hits[j]?"true":"false");
}
*/
