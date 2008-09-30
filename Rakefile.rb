
task :clean => [] do
    sh "rm -f *.o"
end

INC = FileList[ '*.h' ]
SRC = FileList[ '*.cpp' ]
OBJ = SRC.sub( /\.cpp$/, '.o' )


rule '.o' => SRC do |t|
    sh %{g++ -c -g -o #{t.name} #{t.source}}
end


file "testpp" => [ :compile ] do |t|
    sh "g++ -o testpp #{OBJ}"
end



task :default => [ :build ]


desc "Compile all source files into objects"
task :compile => OBJ


desc "Build the main executable"
task :build => [ "testpp" ]

