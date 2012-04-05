noinst_PROGRAMS = fptree

fptree_SOURCES =				\
	src/itemset.cc				\
	src/itemset.hh				\
	src/main.cc				\
	src/transactions.cc			\
	src/transactions.hh			\
	src/types.hh				\
	src/parser.hh				\
	src/parser.cc				\
	src/fptree.hh				\
	src/fptree.cc				\
	src/meminfo.hh				\
	src/meminfo.cc

fptree_CXXFLAGS = -std=c++0x
fptree_CPPFLAGS = -I$(top_srcdir)/src
if WINDOWS
fptree_LDADD = -lpsapi
endif
