<?php


class DocumentProcessor {
    
    /**
     * Store the original file
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $return_type 
     */
    public function preserveOriginalDocument($args=null, $dsid, $file, $return_type) {
        
        $_SESSION['fedora_ingest_files']["$dsid"] = $file;

        // Return success 
        return TRUE;
    }
    
    /**
     * Create a PDF thumbnail
     * @param type $parameterArray
     * @param type $dsid
     * @param type $file
     * @param type $return_type
     * @return type 
     */
    public function createThumbnailFromPDFHandler($args=null, $dsid, $file, $return_type) {
        
        // Get the parameters
        $height = $args['height'];
        $width = $args['width'];

        // Create the thumbnail
        $results = $this->convertPDFToThumbnail($file, $width, $height, $dsid, $return_type);

        // Did the create thumbnail fail
        if ($results != false) {
            
            // Add the file to the session
            $_SESSION['fedora_ingest_files']["$dsid"] = $results;
            
            // Return success
            return TRUE;
        }
        
        // Return failed
        return $results;
    }
    
    /**
     * Create a SWF from the pdf
     * @param type $parameterArray
     * @param type $dsid
     * @param type $file
     * @param type $return_type
     * @return type 
     */
    public function createSWFFromPDFHandler($args=null, $dsid, $file, $return_type) {
        
        // Create the thumbnail
        $results = $this->convertPDFToSWF($file);

        // Did the create thumbnail fail
        if ($results != false) {
            
            // Add the file to the session
            $_SESSION['fedora_ingest_files']["$dsid"] = $results;
            
            // Return success
            return TRUE;
        }
        
        // Return failed
        return $results;
    }        
    

    
    /**
     * Convert a document to a pdf
     * @param type $parameterArray
     * @param type $dsid
     * @param type $file
     * @param type $return_type 
     */
    public function createPDFFromDocumentHandler($args=null, $dsid, $file, $return_type) {
    
        // Create the pdf
        $results = $this->convertDocumentToPDF($file);

        // Did the create thumbnail fail
        if ($results != false) {
            
            // Add the file to the session
            $_SESSION['fedora_ingest_files']["$dsid"] = $results;
            
            // Return success 
            return TRUE;
        }

        // Return failed
        return $results;        
    }
    
    /**
     * Create a document thumbnail
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $return_type
     * @return boolean 
     */
    public function createDocumentThumbnailHandler($args, $dsid, $file, $return_type) {

        // Get the parameters
        $height = $args['height'];
        $width = $args['width'];

        $results = null;
        
        // Check to see if we already have the document
        if ( isset($_SESSION['fedora_ingest_files']["OBJ"]) ) {
            
            // Found previous results
            $results = $_SESSION['fedora_ingest_files']["OBJ"];
        } else {
            
            // Create a temp pdf
            $results = $this->convertDocumentToPDF($file);
        }

        // Did the create thumbnail fail
        if ($results != false) {

            // Create the thumbnail
            $results = $this->convertPDFToThumbnail($results, $width, $height, $dsid, $return_type);

            // Did the create thumbnail fail
            if ($results != false) {
            
                // Add the file to the session
                $_SESSION['fedora_ingest_files']["$dsid"] = $results;
            
                // Return success
                return TRUE;
            }
            
            // Return failed
            return $results;
        }
        
        // Return failed
        return $results;
    }
    
    /**
     * Create a swf from the document
     * @param type $args
     * @param type $dsid
     * @param type $file
     * @param type $return_type
     * @return boolean 
     */
    public function createSWFFromDocumentHandler($args, $dsid, $file, $return_type) {

        $results = null;
        
        // Check to see if we already have the document
        if ( isset($_SESSION['fedora_ingest_files']["OBJ"]) ) {
            
            // Found previous results
            $results = $_SESSION['fedora_ingest_files']["OBJ"];
        } 
        else {
            
            // Create a temp pdf
            $results = $this->convertDocumentToPDF($file);
        }

        // Did the create thumbnail fail
        if ($results != false) {


            // Create the thumbnail
            $results = $this->convertPDFToSWF($results);

            // Did the create thumbnail fail
            if ($results != false) {
            
                // Add the file to the session
                $_SESSION['fedora_ingest_files']["$dsid"] = $results;
            
                // Return success
                return TRUE;
            }

            // Return failed
            return $results;
            
        }
        
        // Return failed
        return $results;
    }

    
    /******************************************************/
    // Private Helper functions
    /******************************************************/
    
    /**
     * Convert the document to a pdf
     * @param type $file
     * @return boolean|string 
     */
    private function convertDocumentToPDF($source_file) {
        
        // Get just the file name without the extension
        $file_name = explode('.', basename($source_file));
        $file_dir = dirname($source_file);
        $dest_file = $file_dir . '/' . $file_name[0] . '.pdf';

        // Create the command to execute
        $jobconverter = drupal_get_path('module', 'islandora_docs_sp') . '/lib/jodconverter-cli-2.2.2.jar ';
        $cmdline = '/usr/bin/java -jar ' . $jobconverter . ' ' . $source_file . ' ' . $dest_file;
        
        // Create the return variables
        $output=array();
        $return_value = TRUE;

        // Run the command
        exec($cmdline, $output, $return_value);
        
        // Did it succeed 
        if ($return_value !== FALSE) {

            // return the new file name
            return $dest_file;
        }
        else {
            // return failed
            return false;
        }
    }
    
    /**
     * Create a thumbnail of a pdf
     * @param type $file
     * @param type $width
     * @param type $height
     * @param type $return_type
     * @return boolean 
     */
    private function convertPDFToThumbnail($file, $width, $height, $dsid, $return_type) {

        // Create a file extension
        $file_suffix = '_' . $dsid . '.' . $return_type;
        
        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
      
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {
            $cmdline = "/usr/local/bin/convert \"$file\"\[0\] -flatten -colorspace RGB -thumbnail $width" . "x$height \"$file$file_suffix\"";
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {
            // Use this for Mac OS X (MAMP)
            $cmdline = "sips -s format jpeg \"$file\" -z $height $height --out \"$file$file_suffix\" >/dev/null";
        }
        else {
            $cmdline = "convert \"$file\"\[0\] -colorspace RGB -flatten -thumbnail " . $width . "x" . $height . " \"$file$file_suffix\"";
        }

        // Create the return variables
        $output=array();
        $return_value = TRUE;

        // Run the command
        exec($cmdline, $output, $return_value);

        // Did it succeed 
        if ($return_value !== FALSE) {
      
            // return the new file name
            return $file . $file_suffix;
        }
        else {
            
            // return failed
            return false;
        }
    }
    
    /**
     * Create SWF from PDF
     * @param type $source_file
     * @return string|boolean 
     */
    private function convertPDFToSWF($source_file) {
      
        // Get just the file name without the extension
        $file_name = explode('.', basename($source_file));
        $file_dir = dirname($source_file);
        $dest_file = $file_dir . '/' . $file_name[0] . '.swf';

        $application = "";
        
        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
            $application = "";
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {
            $application = "/usr/bin/pdf2swf";
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {
            $application = "/opt/local/bin/pdf2swf";
        }
        else {
            $application = "";
        }
        
        $cmdline = $application ." ". $source_file ." -o ". $dest_file ." -T 9 -f";

        // Create the return variables
        $output=array();
        $return_value = TRUE;

        // Run the command
        exec($cmdline, $output, $return_value);

        // Did it succeed 
        if ($return_value !== FALSE) {

            // return the new file name
            return $dest_file;
        }
        else {
            
            // return failed
            return false;
        }
    }
}   
