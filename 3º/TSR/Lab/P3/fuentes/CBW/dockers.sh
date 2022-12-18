for i in client broker worker
do
	cd $i; docker build -t $i .; cd ..
done
