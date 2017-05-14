pipeline {
    agent {
        label "mingw64"
    }

    stages {
        stage('Build') { 
            steps {
                // bat 'C:\\msys64\\msys2_shell.cmd -mingw64 -here -c "cmake . -DCMAKE_BUILD_TYPE=Release"'
                sh 'cmake . -DCMAKE_BUILD_TYPE=Release'
                sh 'make'
                // sh 'make doxygen'
                // archiveArtifacts allowEmptyArchive: true, artifacts: 'doxygen/**/*'
            }
        }
        stage('Test'){
            steps {
                // bat 'C:\\msys64\\msys2_shell.cmd -mingw64 -here -c "make run_tests"'
                bat 'sh run_tests'
                // junit 'unit_test.xml'
            }
        }
    }
}

