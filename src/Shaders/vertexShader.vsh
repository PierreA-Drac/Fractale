#version 130

/* Variable globale. */

/* Matrice model-view-projection */
uniform mat4 mvpMatrix;

/* Variable entrante. */

/* Vertex à traiter. */
in vec4 vertex;

/* Variable sortante. */

/* Coordonnées du vertex. */
out vec4 quad;

void main()
{
    /* Transfert des coordonnées du vertex au Fragment Shader. */
    quad = vertex;
    /* Calcul de la position du vertex pour la
     * rastérisation (matricialisation). */
    gl_Position = mvpMatrix * vertex;
}
