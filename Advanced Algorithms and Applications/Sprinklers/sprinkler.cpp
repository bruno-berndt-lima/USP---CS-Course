#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>

using namespace std;

struct Ti {
    double l, r;
} a[11000];

double aa(Ti x,Ti y) {
    if(x.l != y.l)
        return x.l < y.l;
    else
        return x.r > y.r;
}

int main() {
    int t;
    double len, w;
    while(~scanf("%d %lf %lf", &t, &len, &w)) {
        int i,n = 0;
        double maxx = -1.0;
        double c, r;
        for(i = 0; i < t; i++) {
            scanf("%lf %lf", &c, &r);
            if(2 * r <= w) {
                continue;
            } else {
                a[n].l = c - sqrt(r*r-w*w/4);
                a[n++].r = c + sqrt(r*r-w*w/4);
                if((c + sqrt(r*r-w*w/4)) >= maxx) {
                    double rr = c + sqrt(r*r-w*w/4);
                    maxx = max(maxx,rr);
                }
            }
        }
        sort(a,a+n,aa);
        if(a[0].l > 0 || maxx < len) {
            printf("-1\n");
            continue;
        }
        
        double maxx1 = 0;
        int flag = 0, ans = 0;
        while(maxx1 < len) {
            double uu = maxx1;
            for(i = 0; i < n; i++) {
                if(a[i].l <= uu && a[i].r > maxx1) {
                    maxx1 = a[i].r;
                }
            }
            if(uu == maxx1 && uu < len) {
                flag=1;
                break;
            }
            ans++;
        }

        if(flag == 1)
            printf("-1\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}