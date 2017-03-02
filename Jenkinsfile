pipeline {
    agent any 

    stages {
        stage('Build') { 
            steps { 
                sh 'cmake .'
		sh 'make'
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

