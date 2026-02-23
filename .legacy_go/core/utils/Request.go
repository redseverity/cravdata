package utils

import (
	"crypto/tls"
	"net/http"
	"time"
)

// URLCheckResult holds the result of checking a URL
type URLCheckResult struct {
	URL      string `json:"url"`
	Verified bool   `json:"verified"`
	Status   int    `json:"status"`
	Error    string `json:"error,omitempty"`
}

func Request(url string, timeout int) URLCheckResult {
	// Custom transport to skip invalid HTTPS certs
	transport := &http.Transport{
		TLSClientConfig: &tls.Config{InsecureSkipVerify: true},
	}

	client := http.Client{
		Timeout:   time.Duration(timeout) * time.Second,
		Transport: transport,
	}

	req, err := http.NewRequest("GET", url, nil)
	if err != nil {
		return URLCheckResult{
			URL:      url,
			Verified: false,
			Status:   0,
			Error:    err.Error(),
		}
	}

	// Set a common Firefox Headers to avoid blocked
	req.Header.Set("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:121.0) Gecko/20100101 Firefox/121.0")
	req.Header.Set("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8")
	req.Header.Set("Accept-Language", "en-US,en;q=0.9")
	req.Header.Set("Accept-Encoding", "gzip, deflate, br")
	req.Header.Set("Upgrade-Insecure-Requests", "1")
	req.Header.Set("Sec-Fetch-Dest", "document")
	req.Header.Set("Sec-Fetch-Mode", "navigate")
	req.Header.Set("Sec-Fetch-Site", "none")
	req.Header.Set("Sec-Fetch-User", "?1")

	resp, err := client.Do(req)
	if err != nil {
		return URLCheckResult{
			URL:      url,
			Verified: false,
			Status:   0,
			Error:    err.Error(),
		}
	}
	defer resp.Body.Close()

	verified := resp.StatusCode >= 200 && resp.StatusCode < 400

	return URLCheckResult{
		URL:      url,
		Verified: verified,
		Status:   resp.StatusCode,
	}
}
