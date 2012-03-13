<?php


class DocumentProcessor {
    
    /**
     * Convert a document to a pdf
     * @param type $parameterArray
     * @param type $dsid
     * @param type $file
     * @param type $return_type 
     */
    public function createPDFFromDocumentHandler($args=null, $dsid, $file, $return_type) {
        
        // Create the pdf
        $results = $this->convertDocumentToPDF($file, $width, $height, $dsid, $return_type);

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

        // Create a temp pdf
        $results = $this->convertDocumentToPDF($file, $width, $height, 'pdf', 'pdf');

        // Did the create thumbnail fail
        if ($results != false) {

            // Create the thumbnail
            $results = $this->createThumbnailFromPDF($file, $width, $height, $dsid, $return_type);

            // Did the create thumbnail fail
            if ($results != false) {
            
                // Add the file to the session
                $_SESSION['fedora_ingest_files']["$dsid"] = $results;
            
                // Return success
                return TRUE;
            }
        }
        
        // Return failed
        return $results;
    }

    /**
     * create a pdf thumbnail
     * @param type $parameterArray
     * @param type $dsid
     * @param type $file
     * @param type $return_type
     * @return type 
     */
    public function createPDFThumbnailHandler($args=null, $dsid, $file, $return_type) {
        
        // Get the parameters
        $height = $args['height'];
        $width = $args['width'];

        // Create the thumbnail
        $results = $this->createThumbnailFromPDF($file, $width, $height, $dsid, $return_type);

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
    
    /******************************************************/
    // Private Helper functions
    /******************************************************/
    
    /**
     * Convert the document to a pdf
     * @param type $file
     * @return boolean|string 
     */
    private function convertDocumentToPDF($file) {
        
        // Get just the file name without the extension
        $file_name = explode('.', basename($file));
        $file_dir = dirname($file);
        $dest_file = $file_name[0] . '.pdf';
        // Get the file name
        $file = explode('/', $file);
        $file = $file[sizeof($file)-1]; 

        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
            
            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {

            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {

            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        else {

            // Needs fixing
            $application = '/Applications/LibreOffice.app/Contents/MacOS/soffice ';
        }
        
        if ( ! file_exists($file_dir) ) {
            echo("output directory not there!");
        }
        
        if ( !file_exists($file_dir .'/'.$file)) {
            echo("file not there");
        }

        // Build the command to convert the file to a pdf
        $cmdline = $application . ' --headless --verbose --convert-to pdf:writer_pdf_Export --outdir ' . $file_dir . ' ' . $file_dir .'/'.$file;

        $output=array();
        $return_value = TRUE;
        
        exec('ls ' . $file_dir, $output, $return_value);
        var_dump($output);
        var_dump($return_value);
        unset($output);
        
        // Run the command
        //system($cmdline, $return_value);
        exec($cmdline, $output, $return_value);
        var_dump($output);
        var_dump($return_value);
        unset($output);

        // Look again
        exec('ls ' . $file_dir, $output, $return_value);
        var_dump($output);
        var_dump($return_value);
        unset($output);

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
    private function createThumbnailFromPDF($file, $width, $height, $dsid, $return_type) {

        // Create a file extension
        $file_suffix = '_' . $dsid . '.' . $return_type;
        
        if (stristr($_SERVER['SERVER_SOFTWARE'], 'microsoft')) {
      
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'linux')) {
            $cmdline = "/usr/local/bin/convert \"$file\"\[0\] -colorspace RGB -thumbnail $width" . "x$height \"$file$file_suffix\"";
        }
        elseif (stristr($_SERVER['SERVER_SOFTWARE'], 'unix')) {
            // Use this for Mac OS X (MAMP)
            $cmdline = "sips -s format jpeg \"$file\" -z $height $height --out \"$file$file_suffix\" >/dev/null";
        }
        else {
            $cmdline = "convert \"$file\"\[0\] -colorspace RGB -thumbnail " . $width . "x" . $height . " \"$file$file_suffix\"";
        }

        // Create a default error value
        $return_value = TRUE;
        
        // Convert the file
        //var_dump($cmdline);
        system($cmdline, $return_value);

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
}   

?>
