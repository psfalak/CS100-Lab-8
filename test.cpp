#include "../lab-04---composite-pattern-pfala001-akris023/op.hpp"
#include "../lab-04---composite-pattern-pfala001-akris023/rand.hpp"
#include "../lab-04---composite-pattern-pfala001-akris023/mult.hpp"
#include "gtest/gtest.h" 
#include <stdlib.h>
#include <string>  
#include "../lab-04---composite-pattern-pfala001-akris023/div.hpp"
#include "../lab-04---composite-pattern-pfala001-akris023/add.hpp"
#include "../lab-04---composite-pattern-pfala001-akris023/sub.hpp"
#include "../lab-04---composite-pattern-pfala001-akris023/pow.hpp"
#include "../lab-06---strategy-pattern-pfala001-akris023-lab6/container.hpp"
#include "iterator.hpp"
#include "visitor.hpp" 
#include <iostream> 

using namespace std; 

TEST(IteratorTest, PowBinaryTest) {
    	Base* num1 = new Op(3); 
	Base* num2 = new Op(7);
	Base* num3 = new Op(0);  
	Pow* temp = new Pow(num1, num2); 
	Base* dummy = new Add(temp, num3); 
	Iterator *it = new PreorderIterator(dummy); 
	CountVisitor* visit = new CountVisitor(); 
	it->first();
	while(!it->is_done()){
		Base* phase = it->current();
		phase->accept(visit);
		cout << "Stringify phase --> " << phase->stringify() << endl; 
		it->next(); 
	}

	EXPECT_EQ(visit->op_count(), 3);
        EXPECT_EQ(visit->pow_count(), 1);
        EXPECT_EQ(visit->add_count(), 0);
}


TEST(IteratorTest, PowAddTest) {
        Base* num1 = new Op(3);
        Base* num2 = new Op(7);
	Base* num3 = new Op(2); 
        Pow* temp = new Pow(num1, num2);
	Add* temp2 = new Add(temp, num3); 
        Base* dummy = new Add(temp2, num2);

        Iterator *it = new PreorderIterator(dummy);

        CountVisitor* visit = new CountVisitor();
        it->first();
        while(!it->is_done()){
                Base* phase = it->current();
                phase->accept(visit);
                it->next();
        }

        EXPECT_EQ(visit->op_count(), 4);
        EXPECT_EQ(visit->pow_count(), 1);
        EXPECT_EQ(visit->add_count(), 1);
}


TEST(IteratorTest, PowAddSubTest) {
        Base* num1 = new Op(3);
        Base* num2 = new Op(7);
        Base* num3 = new Op(2);
        Pow* temp = new Pow(num1, num2);
        Add* temp2 = new Add(temp, num3);
 	Sub* temp3 = new Sub(temp2, temp); 
        Base* dummy = new Add(temp3, num2);

        Iterator *it = new PreorderIterator(dummy);

        CountVisitor* visit = new CountVisitor();
        it->first();
        while(!it->is_done()){
                Base* phase = it->current();
                phase->accept(visit);
                it->next();
		cout << "Stringify phase --> " << phase->stringify() << endl;
        }

        EXPECT_EQ(visit->op_count(), 6);
        EXPECT_EQ(visit->pow_count(), 2);
        EXPECT_EQ(visit->add_count(), 1);
	EXPECT_EQ(visit->sub_count(), 1);
}

TEST(visitorTest, VisitorTest1){

	CountVisitor* visitor = new CountVisitor(); 
	Base* num1 = new Op(8); 
	Base* num2 = new Op(4); 
	
	num1->accept(visitor); 
	EXPECT_EQ(visitor->op_count(), 1);
	num2->accept(visitor); 
	EXPECT_EQ(visitor->op_count(), 2);

	Base* temp1 = new Sub(num1, num2); 
	Base* temp2 = new Div(num1, num2); 

	temp1->accept(visitor); 
	temp2->accept(visitor);
	
	EXPECT_EQ(visitor->op_count(), 2);
	EXPECT_EQ(visitor->sub_count(), 1);
	EXPECT_EQ(visitor->div_count(), 1);

}

TEST(visitorTest, VisitorTest2){

        CountVisitor* visitor = new CountVisitor();
        Base* num1 = new Op(8);
        Base* num2 = new Op(4);
	Base* num3 = new Op(7); 

        num1->accept(visitor);
        EXPECT_EQ(visitor->op_count(), 1);
        num2->accept(visitor);
        EXPECT_EQ(visitor->op_count(), 2);
	num3->accept(visitor); 
	EXPECT_EQ(visitor->op_count(), 3);

        Base* temp1 = new Sub(num1, num2);
        Base* temp2 = new Div(num1, num2);
	Base* temp3 = new Mult(num3, num2); 
		

        temp1->accept(visitor);
        temp2->accept(visitor);
	temp3->accept(visitor); 	

        EXPECT_EQ(visitor->op_count(), 3);
        EXPECT_EQ(visitor->sub_count(), 1);
        EXPECT_EQ(visitor->div_count(), 1);
	EXPECT_EQ(visitor->mult_count(), 1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
