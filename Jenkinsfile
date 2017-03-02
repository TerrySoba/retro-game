pipeline {
    agent any 

    stages {
        stage('Build') { 
            steps { 
                sh 'cmake .'
		sh 'make'
		sh 'make doxygen'
		archiveArtifacts allowEmptyArchive: true, artifacts: 'doxygen/**/*'
            }
        }
        stage('Test'){
            steps {
                sh 'make run_tests'
                junit 'unit_test.xml'
            }
        }
    }
}

