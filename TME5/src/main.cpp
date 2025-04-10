#include "Vec3D.h"
#include "Rayon.h"
#include "Scene.h"
#include "Job.h"
#include "Pool.h"
#include "Barrier.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <limits>
#include <random>

using namespace std;
using namespace pr;


void fillScene(Scene & scene, default_random_engine & re) {
	// Nombre de spheres (rend le probleme plus dur)
	const int NBSPHERES = 250;

	// on remplit la scene de spheres colorees de taille position et couleur aleatoire
	uniform_int_distribution<int> distrib(0, 200);
	uniform_real_distribution<double> distribd(-200, 200);
	for (int i = 0; i < NBSPHERES; i++) {
		// position autour de l'angle de la camera
		// rayon entre 3 et 33, couleur aleatoire
		// distrib(re) rend un entier aleatoire extrait de re
		scene.add(Sphere({50+distribd(re),50 + distribd(re),120 + distribd(re) }, double(distrib(re)%30) + 3.0, Color::random()));
	}
	// quelques spheres de plus pour ajouter du gout a la scene
	scene.add(Sphere({50,50,40},15.0,Color::red));
	scene.add(Sphere({100,20,50},55.0,Color::blue));

}





// produit une image dans path, représentant les pixels.
void exportImage(const char * path, size_t width, size_t height, Color * pixels) {
	// ppm est un format ultra basique
	ofstream img (path);
	// P3 signifie : les pixels un par un en ascii
	img << "P3" << endl; // ascii format, colors
	// largeur hauteur valeur max d'une couleur (=255 un char)
	img << width  << "\n"<< height << "\n" << "255" << endl;
	// tous les pixels au format RGB
	for (size_t  y = 0 ; y < height ; y++) {
		for (size_t x =0 ; x < width ; x++) {
			Color & pixel = pixels[x*height + y];
			img << pixel << '\n';
		}
	}
	// oui ca fait un gros fichier :D
	img.close();
}

// NB : en francais pour le cours, preferez coder en english toujours.
// pas d'accents pour eviter les soucis d'encodage

int main () {

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	// on pose une graine basee sur la date
	default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	// definir la Scene : resolution de l'image
	Scene scene (1000,1000);
	// remplir avec un peu d'aléatoire
	fillScene(scene, re);
	
	// lumieres 
	vector<Vec3D> lights;
	lights.reserve(3);
	lights.emplace_back(Vec3D(50, 50, -50));
	lights.emplace_back(Vec3D(50, 50, 120));
	lights.emplace_back(Vec3D(200, 0, 120));

	// les points de l'ecran, en coordonnées 3D, au sein de la Scene.
	// on tire un rayon de l'observateur vers chacun de ces points
	// const Scene::screen_t & screen = scene.getScreenPoints();

	// // Les couleurs des pixels dans l'image finale
	Color * pixels = new Color[scene.getWidth() * scene.getHeight()];

	// // pour chaque pixel, calculer sa couleur
	// for (int x =0 ; x < scene.getWidth() ; x++) {
	// 	for (int  y = 0 ; y < scene.getHeight() ; y++) {
	// 		// le point de l'ecran par lequel passe ce rayon
	// 		auto & screenPoint = screen[y][x];
	// 		// le rayon a inspecter
	// 		Rayon  ray(scene.getCameraPos(), screenPoint);

	// 		int targetSphere = findClosestInter(scene, ray);

	// 		if (targetSphere == -1) {
	// 			// keep background color
	// 			continue ;
	// 		} else {
	// 			const Sphere & obj = *(scene.begin() + targetSphere);
	// 			// pixel prend la couleur de l'objet
	// 			Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
	// 			// le point de l'image (pixel) dont on vient de calculer la couleur
	// 			Color & pixel = pixels[y*scene.getHeight() + x];
	// 			// mettre a jour la couleur du pixel dans l'image finale.
	// 			pixel = finalcolor;
	// 		}

	// 	}
	// }
	// const int NBTHREAD = 10;
	// const int NBJOB = 20;

	// vector<int> results(20);
	Pool pool(15);

	pool.start(5);
	Barrier b(scene.getWidth()*scene.getHeight());

	for (int x = 0 ; x < scene.getWidth(); x++) {
		for (int  y = 0 ; y < scene.getHeight(); y++) {
			cout << x << " " << y << "\r";
   			pool.submit(new ConcretJob(&scene, &lights, x, y, &b, &pixels[y*scene.getHeight() + x]));
		}
	}

	cout << "Hello it's me Luigi "  << endl;
	b.waitFor();
	cout << "Hello it's me Mario " << endl;
	pool.stop();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	    std::cout << "Total time "
	              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
	              << "ms.\n";

	exportImage("toto.ppm",scene.getWidth(), scene.getHeight() , pixels);
	cout << "Hello it's me Mario " << endl;
	return 0;
}