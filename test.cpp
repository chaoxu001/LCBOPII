#include <iostream>
#include <Eigen/Dense>
#include <deque>
#include <cmath>
#include "atom.h"
#include "lcbopii.h"
#include "printers.h"

using namespace  simul;

void test_G(LCBOPII lcbopii)
{
	double y = -1.0;
	double step =2/50.0; // 1 - (-1)
	double z = 0.0;
	double y0;

	while(z <= 8)
	{
		y = -1.0;
		std::cout << "# z=" << z << std::endl;

		while(y <= 1.0)
		{
			std::cout << y << " " << lcbopii.G(y,z) << std::endl;
			//std::cout << y << " " << lcbopii.G_1(y) << std::endl;
			//std::cout << std::pow((1 - y), 2) << std::endl;
			y += step;
		}
		y0 = lcbopii.y_0(z);
		//std::cout << "G_1(y0) = " << lcbopii.G_1(y0) << " G_2(y0) = " << lcbopii.G_2(y0, z, y0) << std::endl;
		//std::cout << "G_1_prim(y0) = " << lcbopii.G_1_prim(y0)
		//	     << " G_2_prim(y0) = " << lcbopii.G_2_prim(y0, z, y0) << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		z += 1.0;
	}
}

void test_H(LCBOPII lcbopii)
{
	double x = -1.25;
	double step = (2.5)/400;

	while(x < 1.25)
	{

		//std::cout << "# H_2(d) =" << lcbopii.H_2(lcbopii.d) << std::endl;
		//std::cout << "# H_2_prim(d) =" << lcbopii.H_2_prim(lcbopii.d) << std::endl;
		//std::cout << "# H_3(d) =" << lcbopii.H_3(lcbopii.d) << std::endl;
		std::cout << x << " " << lcbopii.H(x) << std::endl;
		x += step;
	}
}

/*class Test
{
	virtual void dupa();
};
*/
/*
class TestAnalizer: public Atom::StructAnalizer
{
	virtual void bound_found(Atom *u, Atom *v)
	{
		std::cout << "Atom: " << u->get_id() << " --- " << v->get_id() << std::endl;
	}
	virtual void atom_found(Atom *u)
	{
		std::cout << "Odwiedzilem Atom: " << u->get_id() << std::endl;
	}

};
*/

int main()
{

	//Atom::bond_type atoms, atoms2;
	/*std::deque<Atom *> atoms;
   for(int i=0; i<10; i++)
   {

	   Atom * a = new Atom(i*2.0, i/2.0, i/3.0);
	   a->id = i;
	   atoms.push_back(a);
   }

   for(std::deque<Atom *>::iterator it = atoms.begin(); it != atoms.end()-1; it++)
   {
	   Atom * a = *it;
	   a->addBond(*(it+1));
   }

   atoms[3]->removeBond(atoms[0]);

   for(std::deque<Atom *>::iterator it = atoms.begin(); it != atoms.end(); it++)
   {
	   Atom * a = *it;
	   std::cout<< a->id << " bonds:" << std::endl;
	   for(Atom::bond_type::iterator jt = a->get_bonds().begin(); jt != a->get_bonds().end(); jt++)
	   {
		   std::cout << "\t" << (*jt)->id << std::endl;
	   }
   }*/

	double r = 1.7 + 0.1;
	double omega = 2.0*M_PI/3.0;

	Atom * i = new Atom(0.0, 0, 0.0);
	Atom * k1 = new Atom(r*std::cos(omega), r*std::sin(omega), 0.0);
	Atom * k2 = new Atom(r*std::cos(2*omega), r*std::sin(2*omega), 0.0);


	Atom * j = new Atom(r, 0.0, 0.0);
	Atom * l1 = new Atom(r*std::cos(omega + M_PI) + r, r*std::sin(omega + M_PI), 0.0);
	Atom * l2 = new Atom(r*std::cos(2*omega + M_PI) + r, r*std::sin(2*omega + M_PI), 0.0);

	i->addBond(j);
	i->addBond(k1);
	i->addBond(k2);

	j->addBond(l1);
	j->addBond(l2);

	Eigen::Vector3d ri = i->r - j->r;

	double theta = M_PI/2;
	Eigen::AngleAxisd rot_ri(theta, ri.normalized());

	Eigen::Vector3d r_k1_rot = rot_ri * (k1->r - i->r);
	//std::cout << r_k1_rot << std::endl;

	k1->r += (r_k1_rot - k1->r);

	Eigen::Vector3d r_k2_rot = rot_ri * (k2->r - i->r);
	k2->r += (r_k2_rot - k2->r);

	SdfPrinter * aw = new SdfPrinter();
	std::cout << aw->get_sdf(k1);

	//std::cout << std::endl;
	//aw->walk_BFS(k2);

	//std::cout << std::endl;
	//Atom::walk_BFS(i, new TestAnalizer());
	//LCBOPII lcbopii;// = new LCBOPII();

	//test_H(lcbopii);
	/*
	std::cout << lcbopii.F_A_T(i, j, true, false, false) << std::endl;
	std::cout << lcbopii.F_A_T(i, j, false, true, false) << std::endl;
	std::cout << lcbopii.F_A_T(i, j) << std::endl;
	*/
	/*
   std::cout << "H_2(d)" << lcbopii.H_2(lcbopii.d) << std::endl;
   std::cout << "H_3(d)" << lcbopii.H_3(lcbopii.d) << std::endl;*/

	return 1;
}
