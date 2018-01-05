#version 130

/* Variables globales. */

/* Itération maximum d'un point. */
uniform int n_max;
/* Constante complexe c. */
uniform vec2 c;
/* Valeur maximale du module (au carrée). */
uniform float z_max;
/* Valeur initiale des itérations. */
uniform float z_0;
/* Booléen indiquant si la rendu se fait en couleur. */
uniform bool b_color;

/* Facteur de zoom. */
uniform float scale;
/* Centre de l'image. */
uniform vec2 center;

/* Variable entrante. */

/* Coordonnées du vertex. */
in vec4 quad;

void main()
{
    /* Initialisation à z0, itération 0 et couleur noir. */
    vec2 z;
    z.x = z_0 + quad.x;
    z.y = z_0 + quad.y;
    vec4 color = vec4(0.0);
    float i = 0;            /* float car utilisé dans une division pour la
                               couleur. */

    /* Applique le facteur de zoom et centre la fractale (ou déplace si on à
     * déplacer le centre de l'image). */
    z.x = z.x * scale + center.x;
    z.y = z.y * scale + center.y;

    /* Itération du polynôme complexe tant que l'on atteint pas l'itération
     * maximale. Si le point diverge (ne fait pas partie de la fractale car
     * distance OM >= z_max), on arrête. */
    for (i = 0; (i < n_max) && (z.x*z.x + z.y*z.y <= z_max); i++)
    {
        /* z = z^2 + c */
        float tmp = z.x;
        z.x = (z.x * z.x) - (z.y * z.y) + c.x;
        z.y = 2 * tmp * z.y + + c.y;
    }

    /* Si le point ne fait pas partie de la fractale. */
    if (i < n_max - 1) {
        /* Si pas de couleur, pixel blanc. */
        if (b_color == false)
            color = vec4(1.0);
        /* Sinon, couleur en fonction du nombre d'itération. */
        else {
            /* x = rouge ; y = vert ; z = bleu
             * Le résultat doit être compris entre 0 et 1. */
            color.x = sin(i / 100.0);
            color.y = sin(i / 70.0);
            color.z = cos(i / 20.0 + 0.75);
        }
    }

    /* Sortie de la couleur du pixel. */
    gl_FragColor = color;
}
