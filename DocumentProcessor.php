<?php


class DocumentProcessor 
{
    private $pid;
    
    
    public function __construct($pid) {
        var_dump($pid);
        $this->pid = $pid;
    }
    
    /**
     * Ingest is a hook called from the content model 
     */
    public function ingest() {

        // Dump the args
        //var_dump( "ingest: " . func_get_args() );
        
        //var_dump($parameterArray);
        //var_dump($dsid);
        //var_dump($file);
        //var_dump($file_ext);
        
        //$this->createPDF();
        //$this->createThumbnail();
    }
    
    /**
     * Display Thumbnail is a hook called from the content model 
     */
    public function displayThumbnail() {
        
        // Dump the args
        //var_dump("displayThumbnail: " . func_get_args() );
    }
    
    
    public function createDerivatives() {
        
        // Dump the args
        //var_dump("createDerivatives: " . func_get_args() );
    }
    /**
     * Create a pdf 
     */
    public function createPDF() {
        
    }
    
    /**
     * Create a thumbnail 
     */
    public function createThumbnail() {
        
    }
}

?>
