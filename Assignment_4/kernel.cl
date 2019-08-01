typedef struct _cords
{
    int x;
    int y;
    float length;
} cords;
__kernel 
void cart(__global cords* coordinates, const int N, const int M){
    int i = get_global_id(0);
    if(i<N){
        size_t j=0;
        for(j; j<M; j++){
            if(j==0){
                coordinates[i*M+j].length = sqrt( pow((coordinates[i*M+j].x-0),2) + pow((coordinates[i*M+j].y-0),2) );
            }else{
                coordinates[i*M+j].length = coordinates[i*M+(j-1)].length + sqrt( pow((coordinates[i*M+j].x-coordinates[i*M+(j-1)].x),2) + pow((coordinates[i*M+j].y-coordinates[i*M+(j-1)].y),2) );
            }
        }
        j--;
        if(i>0){
            if(min(coordinates[i*M+j].length, coordinates[(i-1)*M+j].length) ==  coordinates[i*M+j].length){
                for(size_t k=0;k<M;k++){
                    cords temp = coordinates[(i-1)*M+k];
                    coordinates[(i-1)*M+k] = coordinates[i*M+k];
                    coordinates[i*M+k] = temp;
                }
            }
        }
        if(i<N-1){
            if(max(coordinates[i*M+j].length, coordinates[(i+1)*M+j].length) ==  coordinates[i*M+j].length){
                for(size_t k=0;k<M;k++){
                    cords temp = coordinates[(i+1)*M+k];
                    coordinates[(i+1)*M+k] = coordinates[i*M+k];
                    coordinates[i*M+k] = temp;
                }
            }
        }
    }
    // if(i==N){

    // }
}
