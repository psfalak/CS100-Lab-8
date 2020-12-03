#ifndef __COUNT_VISITOR_HPP__
#define __COUNT_VISITOR_HPP__

class CountVisitor{
    private:
        int ops = 0;
        int rands = 0;
        int mults = 0;
        int divs = 0;
        int add = 0;
        int sub = 0;
        int pow = 0;

    public:
        CountVisitor();

        void visit_op(){
	   ops += 1;
	}
        int op_count(){
	   return ops;
	}
        void visit_rand(){
	   rands += 1;
	}
        int rand_count(){
           return rands;
        }
        void visit_mult(){
           mults += 1;
        }
        int mult_count(){
           return mults;
        }
        void visit_div(){
           divs += 1;
        }
        int div_count(){
           return divs;
        }
        void visit_add(){
           add += 1;
        }
        int add_count(){
           return add;
        }
        void visit_sub(){
           sub += 1;
        }
        int sub_count(){
           return sub;
        }
        void visit_pow(){
           pow += 1;
        }
        int pow_count(){
           return pow;
        }

};

#endif //__COUNT_VISITOR_HPP__
