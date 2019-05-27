#/bin/sh

echo gurobi: ${GUROBI_HOME:=/opt/gurobi460/linux32}
export GUROBI_HOME

case "$1" in
  cc)
	g++ -O2 -s -Wall -W $2 $3 $4 $5 $6 $7 $8 $9 \
        -I$GUROBI_HOME/include -L$GUROBI_HOME/lib \
        -lgurobi_c++ -lgurobi46 -lpthread \
        -Wl,-rpath $GUROBI_HOME/lib
	;;
  obj)
	g++ -O2 -c -Wall -W $2 $3 $4 $5 $6 $7 $8 $9 \
        -I$GUROBI_HOME/include
	;;
  4)
	rlwrap -c $GUROBI_HOME/bin/gurobi.sh
	;;
  *)
	$0 4
	;;
esac

exit 0

