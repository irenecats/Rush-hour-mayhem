#ifndef INTERPOLACION_H
#define INTERPOLACION_H


class Interpolacion
{
    public:
        Interpolacion();
        Interpolacion(float parX, float parY);
        virtual ~Interpolacion();
        Interpolacion(const Interpolacion& other);
        float Getx() { return x; }
        void Setx(float val) { x = val; }
        float Gety() { return y; }
        void Sety(float val) { y = val; }
    protected:
    private:
        float x = 0;
        float y = 0;
};

#endif // INTERPOLACION_H
