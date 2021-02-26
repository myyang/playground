const Router = require('./router')

import qs from "qs"

/**
 * Github Utils
 *  */
const ghIssueRegex = /(?<owner>\w*)\/(?<repo>\w*)\#(?<issue_number>\d*)/
const parseGhIssueString = text => {
    const match = text.match(ghIssueRegex)
    return match ? match.groups : null
}

const fetchGitHubIssue = (owner, repo, issue_number) => {
    const url = `https://api.github.com/repos/${owner}/${repo}/issues/${issue_number}`
    const headers = { "User-Agent": "simple-worker-slack-bot" }
    return fetch(url, { headers })
}

/**
 * Slack utils
 *  */
const constructGhIssueSlackMessage = (issue, issue_string) => {
    const issue_link = `<${issue.html_url}|${issue_string}>`
    const user_link = `<${issue.user.html_url}|${issue.user.login}>`
    const date = new Date(Date.parse(issue.created_at)).toLocaleDateString()

    const text_lines = [
        `*${issue.title} - ${issue_link}*`,
        issue.body,
        `*${issue.state}* - Created by ${user_link} on ${date}`,
    ]

    return [
        {
            type: "section",
            text: {
                type: "mrkdwn",
                text: text_lines.join("\n"),
            },
            accessory: {
                type: "image",
                image_url: issue.user.avatar_url,
                alt_text: issue.user.login,
            },
        },
    ]
}


/**
 * Example of how router can be used in an application
 *  */
addEventListener('fetch', event => {
    event.respondWith(handleRequest(event.request))
})

function handler(request) {
    const init = {
        headers: { 'content-type': 'application/json' },
    }
    const body = JSON.stringify({ some: 'json' })
    return new Response(body, init)
}

async function handleRequest(request) {
    const r = new Router()
    // Replace with the appropriate paths and handlers
    r.post('/github-issue', async request => {
        try {
            const body = await request.text()
            const params = qs.parse(body)
            console.log(params["text"]);
            const text = params["text"].trim()
            const { owner, repo, issue_number } = parseGhIssueString(text)
            console.dir(`owner: ${owner}, repo: ${repo}, issue_number: ${issue_number}`);
            const response = await fetchGitHubIssue(owner, repo, issue_number)
            const issue = await response.json()
            console.dir(`issue: ${issue}`);

            const blocks = constructGhIssueSlackMessage(issue, text)
            console.dir(`blocks: ${blocks}`)

            return new Response(
                JSON.stringify({
                    blocks,
                    response_type: "in_channel",
                }),
                { headers: { "Content-type": "application/json" } },
            )
        } catch (err) {
            console.dir(`error: ${err}`)
            const errorText =
                "Uh-oh! We couldn’t find the issue you provided. We can only find public issues in the following format: `owner/repo#issue_number`."
            return new Response(errorText)
        }
    })

    r.get('/', () => new Response('Hello worker!')) // return a default message for the root route

    let response = await r.route(request)

    if (!response) {
        response = new Response("Not found", { status: 404 })
    }

    return response
}
