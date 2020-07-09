#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>  //função rand
#include <time.h>    //função time
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <algorithm>

using namespace std;

int main(){
	
	srand(time(NULL));	

	ifstream log("log.txt",ios::in);

	if (! log){
		cout << "Arquivo saida.txt nao pode ser aberto" << endl;   
		abort();
	}

	float malha_x, malha_y;
	log >> malha_x;
	log >> malha_y;

//lendo a malha		cout << "malha x e malha y é dada por " << malha_x << " e " << malha_y << endl; 



	float xi,xf,yi,yf;

	log >> xi;
	log >> xf;
	log >> yi;
	log >> yf;

//lendo o tamanho do prédio	cout << "O valor de xi xf yi e yf são " << xi << " " << xf << " " << yi << " " << yf << endl;



	int num_cortes;

	log >> num_cortes;	
	
	float arxi,arxf,aryi,aryf;
	vector<float> rxi,rxf,ryi,ryf;

	for(int i=0;i<num_cortes;i++){
		
		log >> arxi;
		log >> arxf;
		log >> aryi;
		log >> aryf;

		rxi.push_back(arxi);
		rxf.push_back(arxf);
		ryi.push_back(aryi);
		ryf.push_back(aryf);
	}	
//lendo o tamanho de cortes e inserindo os valores em um vector de floats
//	for(int i=0;i<num_cortes;i++) cout << rxi[i]<< " " << rxf[i] << " "<< i << endl;



	int num_roteador;
	
	log >> num_roteador;

	vector<float> custo_roteador, raio_roteador;

	float apoio_custo, apoio_raio;

	for(int i=0;i<num_roteador;i++){
		
		log >> apoio_custo;
		log >> apoio_raio;

		custo_roteador.push_back(apoio_custo);
		raio_roteador.push_back(apoio_raio);
	}
// lendo numero de roteadores e buscando custos e raios
	//for(int i=0;i<num_roteador;i++) cout << custo_roteador[i]<< " " << raio_roteador[i] << " "<< i << endl;

	vector<int> tipo_roteador;
	vector<float> coord[2];

	int tipo_rot_apoio;
	float apoio_x,apoio_y;

	while(! log.eof()){

		log >> tipo_rot_apoio;
		log >> apoio_x;
		log >> apoio_y;
		
		tipo_roteador.push_back(tipo_rot_apoio);
		coord[0].push_back(apoio_x);
		coord[1].push_back(apoio_y);

}
//for(int i=0;i<tipo_roteador.size();i++) cout << tipo_roteador[i]<< " " << coord[0][i] << " "<< coord[1][i] << endl;
// ler as coordenadas e o tipo de roteador presente, ele duplica a ultima saída de roteador, mas não terá grande problemas de aplicação

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *imagem = NULL;

	if(!al_init()) {                                         // testa inicialização da biblioteca
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
	cout  << ALLEGRO_VERSION_STR << endl;

	display = al_create_display(608, 576);                // seta tamanho do display 608,576 = 4*(152,144)

	if(!display) {                                        //testa inicialização do display
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	
	bool primitive =  al_init_primitives_addon();

	if(!primitive) {                                        //testa inicialização do primitive_addon
		fprintf(stderr, "failed to initialize primitives addon!\n");
		return -1;
	}
	bool imag = al_init_image_addon();
	if(!imag) {                                        //testa inicialização do primitive_addon
		fprintf(stderr, "failed to initialize primitives addon!\n");
		return -1;
	}

	al_clear_to_color(al_map_rgb(255,255,255));               // seta cor de fundo do display em um buffer
	
	ALLEGRO_COLOR cor_preta = al_map_rgb(0,0,0);	

	float dx;
	dx = (4*(xf-xi)/(malha_x-1));
	for(int i=0;i<malha_x;i++){ //desenho da grade de malha no eixo x.
			
		al_draw_line(0,4*(xf-xi)-i*dx,4*(yf-yi),4*(xf-xi)-i*dx,cor_preta,0);	
	}
	float dy;
	dy = 4*(yf-yi)/(malha_y-1);
	for(int i=0;i<malha_y;i++){ //idem em y.

		al_draw_line(i*dy,0,i*dy,4*(xf-xi),cor_preta,0);
	}

	for(int i=0;i<num_cortes;i++){ // desenhando retângulo dos cortes
		
		al_draw_filled_rectangle(4*ryi[i],4*rxi[i],4*ryf[i],4*rxf[i], al_map_rgb(112,112,112));
	
	}


	ALLEGRO_COLOR cor_roteador[num_roteador];

	for(int i=0; i<num_roteador;i++){
		
		int x[3];
		for(int j=0;j<3;j++) x[j] = rand()%256;
		cor_roteador[i]=al_map_rgb(x[0],x[1],x[2]);

	}

	
	for (int i= 0; i<coord[0].size();i++){
		
		al_draw_filled_circle(4*coord[1][i],4*coord[0][i],min(dx/2,dy/2),cor_roteador[tipo_roteador[i]]);

		al_draw_circle(4*coord[1][i],4*coord[0][i],4*raio_roteador[tipo_roteador[i]],cor_roteador[tipo_roteador[i]],4);

	
	}
	
	
			   
	al_flip_display();                                    //esvazia o buffer

	al_rest(5.0);                                        // espera 10 segundos

	//al_destroy_display(display);                           // destroi o display
return(0);
}
