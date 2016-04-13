/* Plugin structure generated by Schiavoni Pure Data external Generator */
#include "m_pd.h"

// ---------------------------------------------------
// Class definition
// ---------------------------------------------------
static t_class *biquad_class;

// ---------------------------------------------------
// Data structure definition
// ---------------------------------------------------
typedef struct _biquad {
    t_object x_obj;
    t_inlet * x_inlet_dsp_0;
    t_inlet * x_inlet_dsp_1;
    t_inlet * x_inlet_dsp_2;
    t_inlet * x_inlet_dsp_3;
    t_inlet * x_inlet_dsp_4;
    t_inlet * x_inlet_dsp_5;
    float  x_xnm1;
    float  x_xnm2;
    float  x_ynm1;
    float  x_ynm2;
    t_outlet * x_outlet_dsp_0;
    
} t_biquad;

// ---------------------------------------------------
// Functions signature
// ---------------------------------------------------
void * biquad_new(void);// Constructor
void biquad_destroy(t_biquad *x); //Destructor
void biquad_clear(t_biquad *x); // Message function
static t_int * biquad_perform(t_int *w); //Perform function
static void biquad_dsp(t_biquad *x, t_signal **sp); //DSP function

// ---------------------------------------------------
// biquad_clear
// ---------------------------------------------------
void biquad_clear(t_biquad *x){
   x->x_xnm1 = x->x_xnm2 = x->x_ynm1 = x->x_ynm2 = 0.;
}

// ---------------------------------------------------
// biquad_stoke
// ---------------------------------------------------
void biquad_stoke(t_biquad *x){
}


// ---------------------------------------------------
// Perform
// ---------------------------------------------------
static t_int * biquad_perform(t_int *w){
    t_biquad *x = (t_biquad *)(w[1]);
    int n = (int)(w[2]);
    t_float *xn = (t_float *)(w[3]);
    t_float *a0 = (t_float *)(w[4]);
    t_float *a1 = (t_float *)(w[5]);
    t_float *a2 = (t_float *)(w[6]);
    t_float *b1 = (t_float *)(w[7]);
    t_float *b2 = (t_float *)(w[8]);
    t_float *out = (t_float *)(w[9]);
    float xnm1 = x->x_xnm1;
    float xnm2 = x->x_xnm2;
    float ynm1 = x->x_ynm1;
    float ynm2 = x->x_ynm2;
    while (n--)
    {
    float yn;
//      *out++ = yn = (*xn++ * *a0++) + (xnm1 * *a1++) + (xnm2 * *a2++) - (ynm1 * *b1++) - (ynm2 * *b2++);
        *out++ = yn = (*xn++ * *a0++) + (*a1++) + (*a2++) - (*b1++) - (*b2++);
    xnm2 = xnm1;
    xnm1 = *xn++;
    ynm2 = ynm1;
    ynm1 = yn;
    }
    x->x_xnm1 = xnm1;
    x->x_xnm2 = xnm2;
    x->x_ynm1 = ynm1;
    x->x_ynm2 = ynm2;
    return (w + 10);
}

// ---------------------------------------------------
// DSP Function
// ---------------------------------------------------
static void biquad_dsp(t_biquad *x, t_signal **sp){
    dsp_add(biquad_perform, 9, x, sp[0]->s_n, sp[0]->s_vec, sp[1]->s_vec,
            sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[6]->s_vec);
}

// ---------------------------------------------------
// Constructor of the class
// ---------------------------------------------------
void * biquad_new(void){
    t_biquad *x = (t_biquad *) pd_new(biquad_class);
    
    x->x_inlet_dsp_0 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_inlet_dsp_1 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_inlet_dsp_2 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_inlet_dsp_3 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_inlet_dsp_4 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    x->x_inlet_dsp_5 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
    
    x->x_outlet_dsp_0 = outlet_new(&x->x_obj, &s_signal);
    
    return (void *) x;
}

// ---------------------------------------------------
// Destroy the class
// ---------------------------------------------------
void biquad_destroy(t_biquad *x)
{
    inlet_free(x->x_inlet_dsp_0);
    inlet_free(x->x_inlet_dsp_1);
    inlet_free(x->x_inlet_dsp_2);
    inlet_free(x->x_inlet_dsp_3);
    inlet_free(x->x_inlet_dsp_4);
    inlet_free(x->x_inlet_dsp_5);
    
    outlet_free(x->x_outlet_dsp_0);
}

// ---------------------------------------------------
// Setup
// ---------------------------------------------------
void biquad_tilde_setup(void)
{
    biquad_class = class_new(gensym("cyclone/biquad~"),
                             (t_newmethod) biquad_new, // Constructor
                             (t_method) biquad_destroy, // Destructor
                             sizeof (t_biquad),
                             CLASS_DEFAULT, 0);//Must always ends with a zero
    class_addmethod(biquad_class, (t_method) biquad_clear, gensym("clear"), 0);
    class_addmethod(biquad_class, (t_method) biquad_stoke, gensym("stoke"), 0);
    class_addmethod(biquad_class, (t_method) biquad_dsp, gensym("dsp"), 0);
}