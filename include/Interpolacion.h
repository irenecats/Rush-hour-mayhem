#ifndef INTERPOLACION_H
#define INTERPOLACION_H


class Interpolacion
{
    public:
        Interpolacion();
        virtual ~Interpolacion();
        Interpolacion(const Interpolacion& other);
        float Getx() { return x; }
        void Setx(float val) { x = val; }
        float Gety() { return y; }
        void Sety(float val) { y = val; }
    protected:
    private:
        float x;
        float y;
};

#endif // INTERPOLACION_H
