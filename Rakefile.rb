
task :clean => [] do
    sh "rm -f *.o"
end

INC = FileList[ '*.h' ]
SRC = FileList[ '*.cpp' ]
OBJ = SRC.sub( /\.cpp$/, '.o' )

print OBJ


rule '.o' => SRC do |t|
    sh %{g++ -c -g -o #{t.name} #{t.source}}
end


file "run_testpp" => [ :compile ] do |t|
    sh "g++ -g -o run_testpp #{OBJ}"
end

task :default => [ :build ]


desc "Compile all source files into objects"
task :compile => OBJ


desc "Build the main executable"
task :build => [ "run_testpp" ]

task :full => [] do
    sh "g++ -o run_testpp testpp.cpp testpp_assertion.cpp testpp_test.cpp"
end

