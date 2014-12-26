#include <iostream>
#include "supercubic.h"
using namespace std;
void supercubic_construct_test()
{
 int dimen=3;
 int n[3]={3,5,6};
 Supercubic point;
 Supercubic cubic(dimen, n);
 size_t flag=0;

 if(point.dimen!=0) flag++;
 if(point.L!=0) flag++;
 if(point.Nhop!=0) flag++;

 if(cubic.dimen!=dimen)    flag++;
 for(int i=0; i<dimen;i++) {if(cubic.n[i]!=n[i]) flag++;}
 if(cubic.L!=90) flag++;
 if(cubic.Nhop!=0) flag++;
 if(flag==0) cout<<"Supercubic passed the construction test!\n";
 else cout<<"Warning!!!!Supercubic failed the construction test!\n";
}

void supercubic_equal_test()
{
 int dimen=3;
 int n[3]={3,5,6};
 double t1=-2.0;
 double k[3]={0.12,0.36,9.23};
 size_t flag=0;
 Supercubic cubic_a,cubic_b; 
 Supercubic cubic(dimen, n);
 cubic.set_nn_hop(t1,k);
 cubic.set_dispersion(t1,k);

 //Supercubic cubic_a=cubic; 
 cubic_a=cubic; 
 if(cubic_a.dimen!=cubic.dimen) flag++;
 if(cubic_a.L!=cubic.L) flag++;
 if(cubic_a.Nhop!=cubic.Nhop) flag++;
 for(int i=0; i<cubic_a.Nhop; i++)
 {
  if(cubic_a.siti[i]!=cubic.siti[i]) flag++;
  if(cubic_a.sitj[i]!=cubic.sitj[i]) flag++;
  if(abs(cubic_a.hop[i]-cubic.hop[i])>1e-12) flag++;
 }
 for(int i=0; i<cubic_a.L; i++) {if(abs(cubic_a.dispersion[i]-cubic.dispersion[i])>1e-12) flag++;}
 for(int i=0; i<cubic_a.L; i++) {if(abs(cubic_a.dispersion_inv[i]-cubic.dispersion_inv[i])>1e-12) flag++;}

 //Supercubic cubic_b=std::move(cubic); 
 cubic_b=std::move(cubic); 
 if(cubic_a.dimen!=cubic_b.dimen) flag++;
 if(cubic_a.L!=cubic_b.L) flag++;
 if(cubic_a.Nhop!=cubic_b.Nhop) flag++;
 for(int i=0; i<cubic_a.Nhop; i++)
 {
  if(cubic_a.siti[i]!=cubic_b.siti[i]) flag++;
  if(cubic_a.sitj[i]!=cubic_b.sitj[i]) flag++;
  if(abs(cubic_a.hop[i]-cubic_b.hop[i])>1e-12) flag++;
 }
 for(int i=0; i<cubic_a.L; i++) {if(abs(cubic_a.dispersion[i]-cubic_b.dispersion[i])>1e-12) flag++;}
 for(int i=0; i<cubic_a.L; i++) {if(abs(cubic_a.dispersion_inv[i]-cubic_b.dispersion_inv[i])>1e-12) flag++;}

 if(flag==0) cout<<"Supercubic passed the equal test!\n";
 else cout<<"Warning!!!!Supercubic failed the equal test!\n";
}

void supercubic_coor_test()
{
 int dimen=3;
 int n[3]={3,5,6};
 Supercubic cubic(dimen, n); 
 int ix,iy,iz;

 ix=0;iy=0;iz=0; 
 vector<int> coor;
 size_t flag=0;
 for(int latt=0; latt<cubic.L; latt++)
 {
  coor=cubic.coor(latt);
  if(coor[0]!=ix) flag++;
  if(coor[1]!=iy) flag++;
  if(coor[2]!=iz) flag++;
  ix++;
  if(ix==3) {ix=0;iy++;}
  if(iy==5) {iy=0;iz++;}
  //cout<<coor[0]<<" "<<coor[1]<<" "<<coor[2]<<"\n";
 }
 if(flag==0) cout<<"Supercubic passed the coor test!\n";
 else cout<<"Warning!!!!Supercubic failed the coor test!\n";
}

void supercubic_index_test()
{
 int dimen=3;
 int n[3]={3,5,6};
 Supercubic cubic(dimen,n);
 vector<int> coor;
 size_t flag=0;
 for(int latt=0; latt<cubic.L; latt++)
 {
  coor=cubic.coor(latt);
  if(cubic.index(coor)!=latt) flag++;
 }
 if(flag==0) cout<<"Supercubic passed the index test!\n";
 else cout<<"Warning!!!!Supercubic failed the index test!\n";
}

void supercubic_bound_test()
{
 int dimen=3;
 int n[3]={3,5,6};
 Supercubic cubic(dimen,n);
 size_t flag=0;
 if(cubic.bound(-5,7)!=2) flag++;
 if(cubic.bound(-7,7)!=0) flag++;
 if(cubic.bound(-10,7)!=4) flag++;
 if(cubic.bound(-14,7)!=0) flag++;
 if(cubic.bound(-22,7)!=6) flag++;
 if(cubic.bound(5,7)!=5) flag++;
 if(cubic.bound(7,7)!=0) flag++;
 if(cubic.bound(10,7)!=3) flag++;
 if(cubic.bound(14,7)!=0) flag++;
 if(cubic.bound(22,7)!=1) flag++;
 if(flag==0) cout<<"Supercubic passed the bound test!\n";
 else cout<<"Warning!!!!Supercubic failed the bound test!\n";
 //cout<<flag<<endl;
}

void supercubic_distance_test()
{
 int dimen=2;
 int n[2]={3,4};
 Supercubic square(dimen,n);
 vector<int> coor_i(2),coor_j(2),dist(2),dist_exact(2);
 size_t flag=0;

 coor_i={1,2};coor_j={2,3};dist_exact={1,1};
 dist=square.distance(coor_i,coor_j);
 for(int i=0;i<dimen;i++) {if(dist[i]!=dist_exact[i]) flag++;}

 coor_i={2,3};coor_j={1,2};dist_exact={2,3};
 dist=square.distance(coor_i,coor_j);
 for(int i=0;i<dimen;i++) {if(dist[i]!=dist_exact[i]) flag++;}

 coor_i={1,2};coor_j={2,0};dist_exact={1,2};
 dist=square.distance(coor_i,coor_j);
 for(int i=0;i<dimen;i++) {if(dist[i]!=dist_exact[i]) flag++;}

 if(flag==0) cout<<"Supercubic passed the distance test!\n";
 else cout<<"Warning!!!!Supercubic failed the distance test!\n";

 //cout<<flag<<endl;
}


void supercubic_inverse_test()
{
 int dimen=2;
 int n[2]={3,4};
 Supercubic square(dimen,n);
 size_t flag=0;
 if(square.inverse(0)!=0)  flag++;
 if(square.inverse(1)!=2)  flag++;
 if(square.inverse(2)!=1)  flag++;
 if(square.inverse(3)!=9)  flag++;
 if(square.inverse(4)!=11) flag++;
 if(square.inverse(5)!=10) flag++;
 if(square.inverse(6)!=6)  flag++;
 if(square.inverse(7)!=8)  flag++;
 if(square.inverse(8)!=7)  flag++;
 if(square.inverse(9)!=3)  flag++;
 if(square.inverse(10)!=5)  flag++;
 if(square.inverse(11)!=4)  flag++;

 if(flag==0) cout<<"Supercubic passed the inverse test!\n";
 else cout<<"Warning!!!!Supercubic failed the inverse test!\n";
}

void supercubic_nnhop_test()
{

 int dimen=2;
 int n[2]={3,4};
 Supercubic square(dimen,n);
 double t1=-2.0;
 double k[2]={0.12,0.36};
 square.set_nn_hop(t1,k);

 int siti_exact[]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,11,11,11,11};
 int sitj_exact[]={2,1,9,3,0,2,10,4,1,0,11,5,5,4,0,6,3,5,1,7,4,3,2,8,8,7,3,9,6,8,4,10,7,6,5,11,11,10,6,0,9,11,7,1,10,9,8,2};
 complex<double> hop_exact[]={{-1.9371663222572622,0.4973797743297095},{-1.9371663222572622,-0.4973797743297095},
                              {-1.6886558510040302,1.0716535899579933},{-1.6886558510040302,-1.0716535899579933}};

 size_t flag=0;
 if(square.Nhop!=48) flag++;
 for(int i=0; i<square.Nhop; i++)
 {
  if(square.siti[i]!=siti_exact[i]) flag++;
  if(square.sitj[i]!=sitj_exact[i]) flag++;
  if(abs(square.hop[i]-hop_exact[i%4])>1e-12) flag++;
 }

 if(flag==0) cout<<"Supercubic passed the nnhop test!\n";
 else cout<<"Warning!!!!Supercubic failed the nnhop test!\n";
 //cout<<flag<<endl;

 /*
 int dimen=3;
 int n[3]={3,4,5};
 Supercubic cubic(dimen,n);
 double t1=-2.0;
 double k[3]={0.12,0.36,0.23};
 cubic.set_nn_hop(t1,k);
 for(int i=0; i<cubic.Nhop; i++)
 {
  cout<<i<<": "<<cubic.siti[i]<<" "<<cubic.sitj[i]<<" "<<cubic.hop[i]<<endl;
 }
 */
}

void supercubic_nn_dispersion_test()
{
 int dimen=2;
 int n[2]={3,4};
 Supercubic square(dimen,n);
 double t1=-2.0;
 double k[2]={0.12,0.36};
 square.set_dispersion(t1,k);
 double disp_exact[12]={-7.251644346522585,  -0.5786583399545981, -2.301632419546997,
                        -1.7310254645985386,  4.941960541969448 ,  3.2189864623770488,
                        -0.49702094250646356, 6.175965064061523 ,  4.452990984469124,
                        -6.017639824430509,   0.6553461821374782, -1.0676278974549207};
 double disp_inv_exact[12]={-7.251644346522585, -2.3016324195469977, -0.5786583399545964,
                            -6.0176398244305105, -1.0676278974549238, 0.6553461821374778,
                            -0.497020942506464, 4.452990984469123, 6.175965064061524,
                            -1.731025464598539, 3.218986462377048, 4.941960541969449};

 size_t flag=0;
 for (int i=0; i<square.L; i++) {if(abs(square.dispersion[i]-disp_exact[i])>1e-12) flag++;}
 for (int i=0; i<square.L; i++) {if(abs(square.dispersion_inv[i]-disp_inv_exact[i])>1e-12) flag++;}

 if(flag==0) cout<<"Supercubic passed the nndispersion test!\n";
 else cout<<"Warning!!!!Supercubic failed the nndispersion test!\n";
}

void supercubic_k2_dispersion_test()
{
 int dimen=2;
 int n[2]={3,4};
 Supercubic square(dimen,n);
 double k[2]={0.12,0.36};
 square.set_dispersion(k);
 double disp_exact[12]={0.3829406507622672, 5.822189298473736,  3.716673692908006,
                        4.62687054323069  , 10.06611919094216,  7.960603585376429,
                        6.6994874674594564, 12.138736115170925, 10.033220509605195,
                        1.0738129588385237, 6.513061606549993,  4.407546000984262};
 double disp_inv_exact[12]={0.3829406507622672, 3.7166736929080058, 5.822189298473741,
                            1.0738129588385223, 4.407546000984261, 6.5130616065499956,
                            6.6994874674594564, 10.033220509605195, 12.13873611517093,
                            4.62687054323069, 7.960603585376429, 10.066119190942164};
 size_t flag=0;
 for (int i=0; i<square.L; i++) {if(abs(square.dispersion[i]-disp_exact[i])>1e-12) flag++;}
 for (int i=0; i<square.L; i++) {if(abs(square.dispersion_inv[i]-disp_inv_exact[i])>1e-12) flag++;}
 if(flag==0) cout<<"Supercubic passed the k2dispersion test!\n";
 else cout<<"Warning!!!!Supercubic failed the k2dispersion test!\n";
}

void supercubic_test()
{
 supercubic_construct_test();
 supercubic_equal_test();
 supercubic_coor_test();
 supercubic_index_test();
 supercubic_bound_test();
 supercubic_distance_test();
 supercubic_inverse_test();
 supercubic_nnhop_test();
 supercubic_nn_dispersion_test();
 supercubic_k2_dispersion_test();
}
