#include"intersection.hpp"
intersection::intersection()
{
    
}

intersection::~intersection()
{
}

void intersection::run(std::atomic<bool>* b2){
    loop_runner = b2;
    std::thread t1(&light::run,&tlight,loop_runner);
    while(*loop_runner){
        if(tlight.get_lightAC() == green){
            /**
             * Performs the required left,right,centre checks for each
             * vehicle and direct them were to go applying the delay for right
             * turns and controling traffic
             */
            if(a<a_index && ca.get_inter()==0){
                if(cah[a].get_direc()==rigth || cah[a].get_direc()==straight){
                    cah[a].set_inter(1);
                    ca = cah[a];
                    a++;
                }else
                if(c>=c_index && cah[a].get_direc()==left){
                    cah[a].set_inter(1);
                    ca = cah[a];
                    a++;
                }
            }
            if(c<c_index && cc.get_inter()==0){
                if(cch[c].get_direc()==rigth || cch[c].get_direc()==straight){
                    cch[c].set_inter(1);
                    cc = cch[c];
                    c++;
                }else
                if(a>=a_index && cch[c].get_direc()==left){
                    cch[c].set_inter(1);
                    cc = cch[c];
                    c++;
                }
            }

            if(b<b_index && cb.get_inter()==0){
                // if(!cb.approved){
                //     cb.wait_flag=true;
                // }
                //Removed the wait time
                if(cb.approved && cbh[b].get_direc()==rigth){
                   // if(cc.get_direc()!=straight && ca.get_direc()!=straight){ also removed collision checking
                    if(cc.get_direc()==straight || ca.get_direc()==straight){
                        throw "Crash";
                    }
                    cbh[b].set_inter(1);
                    cb = cbh[b];
                    b++;
                    //}
                }
            }

            if(d<d_index && cd.get_inter()==0){
                // if(!cd.approved){
                //     cd.wait_flag=true;
                // }
                if(cd.approved && cdh[d].get_direc()==rigth){
                    //if(cc.get_direc()!=straight && ca.get_direc()!=straight){
                    if(cc.get_direc()==straight || ca.get_direc()==straight){
                        throw "Crash";
                    }
                        cdh[d].set_inter(1);
                        cd = cdh[d];
                        d++;
                   // }
                }
            }
        }else if(tlight.get_lightBD() == green){
            if(b<b_index && cb.get_inter()==0){
                if(cbh[b].get_direc()==rigth || cbh[b].get_direc()==straight){
                    cbh[b].set_inter(1);
                    cb = cbh[b];
                    b++;
                }else 
                if(d>=d_index && cbh[b].get_direc()==left){
                    cbh[b].set_inter(1);
                    cb = cbh[b];
                    b++;
                }
            }
            if(d<d_index && cd.get_inter()==0){
                if(cdh[d].get_direc()==rigth || cdh[d].get_direc()==straight){
                    cdh[d].set_inter(1);
                    cd = cdh[d];
                    d++;
                }else
                if(b>=b_index && cdh[d].get_direc()==left){
                    cdh[d].set_inter(1);
                    cd = cdh[d];
                    d++;
                }
            }
            if(a<a_index && ca.get_inter()==0){
                // if(!ca.approved){
                //     ca.wait_flag=true;
                // }
                if(ca.approved && cah[a].get_direc()==rigth){
                    if(cb.get_direc()==straight || cd.get_direc()==straight){
                        throw "Crash";
                    }
                    //if(cb.get_direc()!=straight && cd.get_direc()!=straight){
                    cah[a].set_inter(1);
                    ca = cah[a];
                    a++;
                    //}
                }
            }

            if(c<c_index && cc.get_inter()==0){
                // if(!cc.approved){
                //     cc.wait_flag=true;
                // }
                if(cc.approved && cch[c].get_direc()==rigth){
                    if(cb.get_direc()==straight || cd.get_direc()==straight){
                        throw "Crash";
                    }
                    //if(cd.get_direc()!=straight && cb.get_direc()!=straight){
                        cch[c].set_inter(1);
                        cc = cch[c];
                        c++;
                   // }
                }
            }
        }
    }
    t1.join();
}

void intersection::set_car_arrays(car *c1,car *c2,car *c3,car *c4){
    cah=c1;
    cbh=c2;
    cch=c3;
    cdh=c4;
}