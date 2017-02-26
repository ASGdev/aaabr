// déclaration du type file
typedef struct {
    int tete, queue;
    Arbre *T;
} File ;

	// opérations sur les files
// équivalent : File *Create(int size){}
void Create(File *f, int size){
    f->T = malloc(size * sizeof(Arbre));
    f->queue = 0;
    f->tete = 0;
}
void Put (File *F, Arbre a){
    F->T[F->queue] = a;
    F->queue = F->queue + 1;
}
Arbre Get(File *F){
    int save = F->tete;
    F->tete = F->tete + 1;
    return F->T[save];
}
int estVide(File f){
    return (f.queue == f.tete);
}
