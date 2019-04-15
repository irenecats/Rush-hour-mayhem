#include <iostream>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <stdio.h>
#include "Mapa.h"
#include "Jugador.h"
#include "Sprite.h"

using namespace tinyxml2;
using namespace std;

Mapa::Mapa()
{
    //Lector de grafos
    XMLDocument doc;

    doc.LoadFile("FV City Map/newchinatown.tmx");

    XMLElement* grafo= doc.FirstChildElement("map")->FirstChildElement("objectgroup");

    XMLElement* punto=grafo->FirstChildElement("object");

    //Declaracion variables del bucle
    int contador=0;
    XMLElement* adyacente;
    string points;
    int xaux=0;
    int yaux=0;
    string xad;
    string yad;
    int xadj=0;
    int yadj=0;

    while(punto)
    {
        punto->QueryIntAttribute("x",&xaux);
        punto->QueryIntAttribute("y",&yaux);

        adyacente=punto->FirstChildElement("polyline");
        points=adyacente->Attribute("points");
        points=points.substr(points.find(" ") + 1);
        xad=points.substr(0, points.find(","));
        yad=points.substr(points.find(",")+1);
        xadj=std::stoi(xad);
        yadj=std::stoi(yad);

        if(contador!=0)
        {
            bool flag=false;
            bool flag2=false;
            int save=0;
            int save2=0;
            for(int i=0; i<nodos.size(); i++)
            {
                if(nodos[i]->coor[0]==xaux && nodos[i]->coor[1]==yaux)
                {
                    flag=true;
                    save=i;
                    break;
                }
                else
                {
                    flag=false;
                }
            }
            //EL nodo existe
            if(flag==true)
            {
                for(int i=0; i<nodos.size(); i++)
                {
                    if(nodos[i]->coor[0]==(xaux+xadj) && nodos[i]->coor[1]==(yaux+yadj))
                    {
                        flag2=true;
                        save2=i;
                        break;
                    }
                    else
                    {
                        flag2=false;
                    }
                }
                //El nodo adyancente existe
                if(flag2==true)
                {
                    nodos[save]->addAdj(nodos[save2]);
                }
                //El nodo adyacente no existe
                else
                {
                    Node* nuevo=new Node(xaux+xadj,yaux+yadj);
                    nodos[save]->addAdj(nuevo);
                    nodos.push_back(nuevo);
                }
            }
            //El nodo no existe
            else
            {
                Node* nuevo=new Node(xaux,yaux);

                for(int i=0; i<nodos.size(); i++)
                {
                    if(nodos[i]->coor[0]==(xaux+xadj) && nodos[i]->coor[1]==(yaux+yadj))
                    {
                        flag2=true;
                        save2=i;
                        break;
                    }
                    else
                    {
                        flag2=false;
                    }
                }
                //El nodo adyacente existe
                if(flag2==true)
                {
                    nuevo->addAdj(nodos[save2]);
                    nodos.push_back(nuevo);
                }
                //El nodo adyacente no existe
                else
                {
                    Node* nuevo2=new Node(xaux+xadj,yaux+yadj);
                    nuevo->addAdj(nuevo2);
                    nodos.push_back(nuevo);
                    nodos.push_back(nuevo2);
                }
            }
        }
        if(contador==0)
        {

            Node* nuevo=new Node(xaux,yaux);
            Node* nuevo2=new Node(xaux+xadj,yaux+yadj);
            nuevo->addAdj(nuevo2);
            nodos.push_back(nuevo);
            nodos.push_back(nuevo2);
        }
        contador++;
        punto=punto->NextSiblingElement("object");
    }
    //Impresor de la lista de nodos y sus adyacentes, descomentar si se necesita
    /*
    for(int i=0;i<nodos.size();i++){
        cout << "Nodo: " << nodos[i]->coor[0] <<", "<< nodos[i]->coor[1]<<endl;
        cout<< "Adyacentes:" <<endl;
         for(int j=0;j<nodos[i]->adj.size();j++){
            cout << nodos[i]->adj[j]->coor[0] <<", "<< nodos[i]->adj[j]->coor[1]<<endl;
         }
     }*/

    ////////////////////////////////////////////////////////////////////////////////////

    //Mapa
    int _tileWidth;
    int _tileHeight;

    //Impresión de datos generales del mapa

    doc.LoadFile("FV City Map/newchinatown.tmx");

    XMLElement* map= doc.FirstChildElement("map");

    map->QueryIntAttribute("width",&_width);
    map->QueryIntAttribute("height",&_height);
    map->QueryIntAttribute("tilewidth",&_tileWidth);
    map->QueryIntAttribute("tileheight",&_tileHeight);

    cout << _width << "/"<<_height <<"/"<< _tileWidth <<"/"<< _tileHeight <<endl;

    //Impresion de datos sobre las capas disponibles para dibujar
    numlayer=0;

    XMLElement* layer=map->FirstChildElement("layer");
    while(layer)
    {
        numlayer++;
        layer=layer->NextSiblingElement("layer");
    }
    cout<<"Layers: " << numlayer <<endl;


    XMLElement *data[numlayer];

    data[0]=map -> FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");

    int l=0;
    const char* prueba;
    XMLElement* layer2=map->FirstChildElement("layer");
    layer2->QueryStringAttribute("name", &prueba);
    cout << prueba <<endl;

    while(layer2)
    {
        l++;
        layer2=layer2->NextSiblingElement("layer");
        if(l<numlayer)
        {
            data[l]=layer2->FirstChildElement("data")->FirstChildElement("tile");

            layer2->QueryStringAttribute("name", &prueba);
            cout << prueba <<endl;
        }
    }

    //Leer todas las capas cada una con sus gid
    //En esta matriz estan todos los gid de la capa
     const int numcapas=numlayer;
    const int altura=_height;
    const int anchura=_width;

    unsigned int*** _tilemap=new unsigned int**[numcapas];
         for (int i = 0; i < numcapas; i++){
           _tilemap[i] = new unsigned int*[altura]();
             for (int j = 0; j < altura; j++){
                _tilemap[i][j] = new unsigned int[anchura]();
        }}

        int*** tilemapflags=new int**[numcapas];
         for (int i = 0; i < numcapas; i++){
           tilemapflags[i] = new int*[altura]();
             for (int j = 0; j < altura; j++){
                tilemapflags[i][j] = new int[anchura]();
        }}

    for(int z=0; z<numlayer; z++)
    {
        for(int y=0; y<_height; y++)
        {
            for(int x=0; x<_width; x++)
            {
                unsigned int auxnum=0;
                data[z]->QueryUnsignedAttribute("gid", &auxnum);
                int length = 1;
                int n = auxnum;
                while ( n /= 10 )
                    length++;
                if(length>=10)
                {
                    //Rotacion y flip horizontal de tiles restando las mascaras hexadecimales, previamente pasadas a decimal
                    if(auxnum>3221225470)
                    {
                        auxnum-=3221225472;
                        tilemapflags[z][y][x]=180;
                    }
                    else if(auxnum>2684354560)
                    {
                        auxnum-=2684354560;
                        tilemapflags[z][y][x]=90;
                    }
                    else
                    {
                        auxnum-=1610612736;
                        length = 1;
                        n = auxnum;
                        while ( n /= 10 )
                            length++;
                        if(length>=9)
                        {
                            auxnum-=536870912;
                            tilemapflags[z][y][x]=1;
                        }
                        else
                        {
                            tilemapflags[z][y][x]=270;
                        }
                    }
                }
                length = 1;
                n = auxnum;
                while ( n /= 10 )
                    length++;
                if(auxnum==0 || auxnum==NULL)
                {
                    auxnum=0;
                }
                _tilemap[z][y][x]=auxnum;

                data[z]=data[z]->NextSiblingElement("tile");
            }
        }
    }


    //Guardamos los datos de las tiles de todas las texturas en un array unidimensional
    int numtileset=0;
    int tamArray;
    XMLElement* tilesetcounter=map->FirstChildElement("tileset");
    while(tilesetcounter)
    {
        numtileset++;
        int a;
        int b;
        tilesetcounter->QueryIntAttribute("firstgid",&a);
        tilesetcounter->QueryIntAttribute("tilecount",&b);
        tamArray=a+b;
        tilesetcounter=tilesetcounter->NextSiblingElement("tileset");
    }
    cout<<"Num.Tilesets: " << numtileset <<endl;
    cout<<"Num.Tiles: " << tamArray <<endl;
    //Declaramos arrays con la información requerida para crear cada sprite
    sf::IntRect *_tilemapSprite[tamArray];
    int textureinfo[tamArray];
    //sf::Texture aux[numtileset];

    tilesetcounter=map->FirstChildElement("tileset");
    int contar=0; //Contador de texturas
    contador=0; //Contador de gids
    while(tilesetcounter)
    {
        XMLElement *img=tilesetcounter->FirstChildElement("image");
        const char *_tilesetTexture=img->Attribute("source");
        std::string fullfichero(_tilesetTexture);
        fullfichero="FV City Map/"+fullfichero;
        int tamLayerx;
        int tamLayery;
        img->QueryIntAttribute("width",&tamLayerx);
        img->QueryIntAttribute("height",&tamLayery);

        tamLayerx=int(tamLayerx/32);
        tamLayery=int(tamLayery/32);

        TexturaContainer::instancia()->crearTexturaMapa(fullfichero);

        //La ordenacion de las tiles difiere según la proporción de la textura
        if(tamLayerx%tamLayery==0)
        {
            for(int x=0; x<tamLayerx; x++)
            {
                for(int y=0; y<tamLayery; y++)
                {
                    _tilemapSprite[contador]=new sf::IntRect(y*32, x*32, 32, 32);
                    textureinfo[contador]=contar;
                    contador++;
                }
            }
        }
        else
        {
            for(int y=0; y<tamLayery; y++)
            {
                for(int x=0; x<tamLayerx; x++)
                {
                    _tilemapSprite[contador]=new sf::IntRect(x*32, y*32, 32, 32);
                    textureinfo[contador]=contar;
                    contador++;
                }
            }
        }
        contar++;
        tilesetcounter=tilesetcounter->NextSiblingElement("tileset");
    }


    //Recorremos la matriz de gid y buscamos el Sprite que hay que dibujar en la matriz de Sprites,
    //y lo añadimos en una matriz de dibujado definitiva

    dibujar=new Sprite***[numcapas];
    for (int i = 0; i < numcapas; i++)
    {
        dibujar[i] = new Sprite**[altura]();
        for (int j = 0; j < altura; j++)
        {
            dibujar[i][j] = new Sprite* [anchura]();
        }
    }
    for(int z=0; z<numlayer; z++)
    {
        for(int y=0; y<_height; y++)
        {
            for(int x=0; x<_width; x++)
            {

                if(_tilemap[z][y][x]>0)
                {

                    dibujar[z][y][x]=new Sprite(TexturaContainer::instancia()->getTexturaMapa()[textureinfo[_tilemap[z][y][x]-1]],*_tilemapSprite[_tilemap[z][y][x]-1]);

                    dibujar[z][y][x]->setPosition(x*32,y*32);
                    dibujar[z][y][x]->setOrigin(16,16);
                    if(tilemapflags[z][y][x]!=0)
                    {

                        if(tilemapflags[z][y][x]==90)
                        {
                            dibujar[z][y][x]->setRotation(90);
                        }
                        if(tilemapflags[z][y][x]==180)
                        {
                            dibujar[z][y][x]->setRotation(180);
                        }
                        if(tilemapflags[z][y][x]==270)
                        {
                            dibujar[z][y][x]->setRotation(270);
                        }
                        if(tilemapflags[z][y][x]==1)
                        {
                            dibujar[z][y][x]->setScale(-1.f,1.f);
                        }
                    }
                }
                else
                {
                    dibujar[z][y][x]=NULL;
                }
            }
        }
    }

    //Delete de los array reservados en memoria provisionalmente por exceso de tamaño

    for(int i=0;i!= numlayer; ++i){
        for(int j=0;j != _height; ++j){
            delete[] tilemapflags[i][j];
        }
        delete[] tilemapflags[i];
    }
    delete[] tilemapflags;

}
Mapa* Mapa::instancia=nullptr;
Mapa* Mapa::Instance()
{
    if(!instancia)
    {
        instancia=new Mapa;
    }
    return instancia;
}

vector<Node*> Mapa::getGrafo()
{
    return nodos;
}

Sprite**** Mapa::getMapa()
{
    return dibujar;
}
void Mapa::destructorMapa()
{
    for(int i = 0; i != numlayer; ++i)
    {
        for(int j = 0; j != _height; ++j)
        {
            delete[] dibujar[i][j];
        }
        delete[] dibujar[i];
    }
    delete[] dibujar;
}
void Mapa::destructorGrafo()
{
    for (int i = 0; i < nodos.size(); ++i)
    {
        delete nodos[i];
    }
    nodos.clear();
}
void Mapa::renderMapaAbajo(Window &window)
{
    int tilex=Jugador::instancia()->getJugador().getPosition()[0]/32;
    int tiley=Jugador::instancia()->getJugador().getPosition()[1]/32;
    for(int z=0; z<numlayer-2; z++)
    {
        for(int y=0; y<_height; y++)
        {
            for(int x=0; x<_width; x++)
            {
                //Distancia discreta en geometria del taxista (distancia Manhattan)
                if(abs(tilex-x)+abs(tiley-y)<20)
                {
                    if(dibujar[z][y][x]!=NULL)
                    {
                        window.draw(*dibujar[z][y][x]);
                    }
                }
            }
        }
    }
}
void Mapa::renderMapaArriba(Window &window)
{
    int tilex=Jugador::instancia()->getJugador().getPosition()[0]/32;
    int tiley=Jugador::instancia()->getJugador().getPosition()[1]/32;
    for(int y=0; y<_height; y++)
    {
        for(int x=0; x<_width; x++)
        {
            //Distancia discreta en geometria del taxista (distancia Manhattan)
            if(abs(tilex-x)+abs(tiley-y)<20)
            {
                if(dibujar[numlayer-2][y][x]!=NULL)
                {
                    window.draw(*dibujar[numlayer-2][y][x]);
                }
            }
        }
    }
}

    int  Mapa::getNumlayer(){
        return numlayer;
    }
    int  Mapa::getWidth(){
        return _width;
    }
    int  Mapa::getHeight(){
        return _height;
    }
